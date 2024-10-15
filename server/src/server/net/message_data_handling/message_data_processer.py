import socket
from server.actions.login_attempter import LoginAttempter
from server.user_game_instance.user_game_instance import UserGameInstance
from server.actions.full_update_provider import FullUpdateProvider
from server.user_game_instance.game_core.input.mouse.mouse_buttons import MouseButtons
from common.math_lib import (
    PointF
)

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

                full_update_provider = FullUpdateProvider()
                full_update_provider.provide_full_update(conn, user_game_instance)
            elif msg[0:22] == b"LeftMouseButtonPressed":
                user_game_instance.mouse_input.RegisterMouseButtonPressed(MouseButtons.LEFT)
            elif msg[0:23] == b"LeftMouseButtonReleased":
                user_game_instance.mouse_input.RegisterMouseButtonReleased(MouseButtons.LEFT)
            elif msg[0:9] == b"MouseMove":
                mouse_move_parts = msg.split(b"\n")
                x = float(mouse_move_parts[1].decode("utf-8"))
                y = float(mouse_move_parts[2].decode("utf-8"))
                user_game_instance.mouse_position = PointF(x=x, y=y)
