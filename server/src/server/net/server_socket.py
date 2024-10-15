# Copyright 2024 Andreas Åkerberg

import socket
from server.configuration.server_properties import (
    HOST,
    PORT
)
from server.net.client_acceptance_looper import ClientAcceptanceLooper

class ServerSocket:
    def start(self) -> None:

        print(f"Starting server on host: {HOST} and port: {PORT}")

        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
            
            sock.bind((HOST, PORT))
            sock.listen()

            client_acceptance_looper = ClientAcceptanceLooper()
            client_acceptance_looper.begin_loop(sock)

        
