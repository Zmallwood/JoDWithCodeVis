import socket
from server.actions.login_attempter import LoginAttempter

class ClientAcceptanceLooper:
    def begin_loop(self, sock : socket.socket) -> None:
        while True:
            conn, addr = sock.accept()
            with conn:
                print(f"Connected by {addr}")
                while True:
                    try:

                        data = conn.recv(1024)

                        if not data:
                            break
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

                        conn.send(b"Tessst from scoket")
                    except ConnectionResetError:
                        print("Connection reset by peer.")
                        break
