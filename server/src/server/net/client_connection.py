import socket
from server.net.message_data_handling.message_data_processer import MessageDataProcesser

class ClientConnection:
    def __init__(self, conn : socket.socket, addr : socket.AddressInfo) -> None:

        self.conn = conn
        self.addr = addr

    def process(self) -> None:

        with self.conn:

            print(f"Connected by {self.addr}")

            while True:
                try:
                    data = self.conn.recv(1024)

                    if not data:
                        break

                    message_data_processer = MessageDataProcesser()
                    message_data_processer.process_data(self.conn, data)

                    self.conn.send(b"Tessst from scoket")

                except ConnectionResetError:
                    print("Connection reset by peer.")
                    break
