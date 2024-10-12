/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

namespace JoD {
class Engine {
  public:
    void Run();
    
    void SetRunning(bool value) {
        m_running = value;
    }
    
  private:
    void PollEvents();
    
    bool m_running{true};
};
}
