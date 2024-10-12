/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

namespace JoD {
class MouseButton;

class MouseInput {
  public:
    MouseInput();
    
    void RegisterButtonPressed(Uint8 button);
    
    void RegisterButtonReleased(Uint8 button);
    
    bool AnyButtonIsPressed() const;
    
  private:
    std::shared_ptr<MouseButton> m_leftButton;
    std::shared_ptr<MouseButton> m_rightButton;
};
}
