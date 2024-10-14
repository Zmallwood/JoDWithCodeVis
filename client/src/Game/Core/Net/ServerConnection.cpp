/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "ServerConnection.hpp"

namespace JoD {
void ServerConnection::EnsureConnected() {
    m_clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    // specifying address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(m_port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    
    // sending connection request
    connect(
        m_clientSocket, (struct sockaddr*)&serverAddress,
        sizeof(serverAddress));
    
    // sending data
    const char* message = "Hello, server!<END>";
    send(m_clientSocket, message, strlen(message), 0);
}

bool ServerConnection::LoginUser(std::string_view userName, int passwordHash) {
    auto message = std::string("Login\n") + userName.data() + "\n" +
                   std::to_string(passwordHash) + "<END>";
    send(m_clientSocket, message.c_str(), message.length(), 0);
    char buffer[1024] = {0};
    recv(m_clientSocket, buffer, sizeof(buffer), 0);
    auto s = std::string(buffer);
    std::string end = "<END>";
    auto start_position_to_erase = s.find(end);
    s.erase(start_position_to_erase, end.length());
    std::cout << "Received: " << s<< std::endl;
    if (s == "LoginSuccessful")
        return true;
    else
        return false;
}

ServerConnection::~ServerConnection() {
    if (m_clientSocket)
        close(m_clientSocket);
}
}
