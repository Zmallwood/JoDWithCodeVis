#pragma once

namespace JoD {
class FPSCounter {
  public:
    FPSCounter();
    
    void Update();
    
    void Render();
    
  private:
    int m_fps {0};
    int m_ticksLastUpdate {0};
    int m_framesCount {0};
    RID m_ridFPSText {0};
};
}
