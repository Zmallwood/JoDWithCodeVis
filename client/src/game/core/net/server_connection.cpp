/*
 * Copyright 2024 Andreas Åkerberg.
 */
#include "server_connection.hpp"
#include "game/core/instructions/instructions_manager.hpp"

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
}

void ServerConnection::Update() {
  if (m_timerNetUpdate.HasTick()) {
    auto message = std::string("RequestFullUpdate<END>");
    send(m_clientSocket, message.c_str(), message.length(), 0);
    char buffer[1024] = {0};
    recv(m_clientSocket, buffer, sizeof(buffer), 0);
    auto s = std::string(buffer);
    auto label = std::string("ProvideFullUpdate\n");
    auto delim = s.find(label);
    auto s2 = s.substr(delim + label.length());
    auto end = s2.find("<END>");
    s2 = s2.substr(0,end);
    
    _<InstructionsManager>().Clear();
    auto go_on {s2.length() > 0};
    
    while (go_on) {
      auto delim0 = s2.find(",");
      auto imageName = s2.substr(0, delim0);
      auto remaining1 = s2.substr(delim0 + 1);
      auto delim1 = remaining1.find(",");
      auto x = std::stof(remaining1.substr(0, delim1));
      auto remaining2 = remaining1.substr(delim1 + 1);
      auto delim2 = remaining2.find(",");
      auto y = std::stof(remaining2.substr(0, delim2));
      auto remaining3 = remaining2.substr(delim2 + 1);
      auto delim3 = remaining3.find(",");
      auto w = std::stof(remaining3.substr(0, delim3));
      auto remaining4 = remaining3.substr(delim3 + 1);
      auto delim4 = remaining4.find(",");
      auto h = std::stof(remaining4.substr(0, delim4));
      
      _<InstructionsManager>().AddImageDrawInstruction(
        Hash(imageName),
        BoxF {x, y, w, h});
      
      auto delim5 = remaining4.find("\n");
      
      if (delim5 == std::string::npos)
        return;
      else
        s2 = remaining4.substr(delim5 + 1);
    }
  }
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
  if (s == "LoginSuccessful")
    return true;
  else
    return false;
}

void ServerConnection::SendMessage(std::string_view message) {
  auto terminatedMessage = std::string(message.data()) + "<END>";
  send(
    m_clientSocket, terminatedMessage.c_str(), terminatedMessage.length(),
    0);
}

ServerConnection::~ServerConnection() {
  if (m_clientSocket)
    close(m_clientSocket);
}
}
