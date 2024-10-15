#pragma once

namespace JoD {
class ServerConnection {
  public:
    ~ServerConnection();
    
    void EnsureConnected();
    
    void Update();
    
    bool LoginUser(std::string_view userName, int passwordHash);
    
  private:
    int m_clientSocket {0};
    float m_netUpdateSpeed = 3.0f;
    Timer m_timerNetUpdate = Timer(m_netUpdateSpeed);
    
    const std::string m_host {"127.0.0.1"};
    const int m_port {65432};
};
}
