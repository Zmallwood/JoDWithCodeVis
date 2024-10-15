from server.user_game_instance.user_game_instance import UserGameInstance
import socket


class FullUpdateProvider:
    def provide_full_update(self, conn : socket.socket, user_game_instance : UserGameInstance) -> None:
        conn.send(b"ProvideFullUpdate\nGroundGrass,0.0f,0.1f,0.2f,0.1f<END>")
