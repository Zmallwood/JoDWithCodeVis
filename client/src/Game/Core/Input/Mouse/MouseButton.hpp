#pragma once

namespace JoD {
class MouseButton {
  public:
    void Reset();
    
    void RegisterPressed();
    
    void RegisterReleased();
    
    bool HasBeenFiredPickResult();
    
    bool HasBeenReleasedPickResult();
    
    auto GetIsPressed() const {
        return m_isPressed;
    }
    
  private:
    bool m_isPressed {false};
    bool m_hasBeenFired {false};
    bool m_hasBeenReleased {false};
};
}
