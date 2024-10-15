import socket
from pydantic import BaseModel, ConfigDict
from server.net.message_data_handling.message_data_processer import MessageDataProcesser
from server.user_game_instance.user_game_instance import UserGameInstance

class ClientConnection (BaseModel):

    model_config = ConfigDict(arbitrary_types_allowed=True)

    conn : socket.socket
    addr : tuple

    def process(self) -> None:

        with self.conn:

            print(f"Connected by {self.addr}")

            user_game_instance = UserGameInstance()

            while True:
                try:
                    data = self.conn.recv(1024)

                    if not data:
                        break

                    message_data_processer = MessageDataProcesser()
                    message_data_processer.process_data(self.conn, data, user_game_instance)

                    user_game_instance.process()

                except ConnectionResetError:
                    print("Connection reset by peer.")
                    break
