import socket
from server.net.client_connection import ClientConnection

class ClientAcceptanceLooper:
    def begin_loop(self, sock : socket.socket) -> None:

        while True:
            conn, addr = sock.accept()
            client_connection = ClientConnection(conn = conn, addr = addr)
            client_connection.process()
