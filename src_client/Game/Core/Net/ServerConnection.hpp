/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

namespace JoD {
class ServerConnection {
  public:
    ~ServerConnection();
    
    void EnsureConnected();
    
    bool LoginUser(std::string_view userName, int passwordHash);
    
  private:
    int m_clientSocket {0};
    
    const std::string m_host {"127.0.0.1"};
    const int m_port {65432};
};
}
