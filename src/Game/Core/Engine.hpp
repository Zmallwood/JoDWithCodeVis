/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

namespace JoD {
class Engine {
  public:
    void Run();
    
  private:
    void PollEvents();
    
    bool m_running{true};
};
}
