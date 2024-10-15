from server.net.server_socket import ServerSocket

class Server:
    def run(self) -> None:
        print("Running JoD server.")
        server_socket = ServerSocket()
        server_socket.start()
        
