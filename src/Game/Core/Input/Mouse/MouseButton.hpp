#pragma once

namespace JoD {
class MouseButton {
  public:
    void RegisterPressed();
    
    void RegisterReleased();
    
    auto GetIsPressed() const {
        return m_isPressed;
    }
    
  private:
    bool m_isPressed {false};
};
}
