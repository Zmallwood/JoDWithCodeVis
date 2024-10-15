import socket
from server.actions.login_attempter import LoginAttempter
from server.user_game_instance.user_game_instance import UserGameInstance
from server.actions.full_update_provider import FullUpdateProvider

class MessageDataProcesser:

    def process_data(self, conn : socket.socket, data : bytes, user_game_instance : UserGameInstance) -> None:

        msgs = data.split(b"<END>")
    
        for msg in msgs:
    
            if msg[0:6] == b"Login\n":
    
                login_attempter = LoginAttempter()
    
                login_parts = msg.split(b"\n")
                user_name = login_parts[1].decode("utf-8")
                password_hash = int(login_parts[2])
    
                if login_attempter.attempt_login(user_name, password_hash):
                    conn.send(b"LoginSuccessful<END>")

                else:
                    conn.send(b"LoginFailed<END>")
            elif msg[0:17] == b"RequestFullUpdate":

                print("Full update request")
                full_update_provider = FullUpdateProvider()
                full_update_provider.provide_full_update(conn, user_game_instance)

