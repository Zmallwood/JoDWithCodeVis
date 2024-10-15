/*
 * Copyright 2024 Andreas Åkerberg.
 */

#pragma once

namespace JoD {
class MouseButton;

class MouseInput {
  public:
    MouseInput();
    
    void Reset();
    
    void RegisterButtonPressed(Uint8 button);
    
    void RegisterButtonReleased(Uint8 button);
    
    void RegisterMouseMoved(Point2 delta);
    
    void RegisterMouseWheelScrolled(int delta);
    
    bool AnyMouseButtonIsPressed() const;
    
    int GetMouseWheelDeltaPickResult();
    
    Point2 GetMotionDeltaPickResult();
    
    auto GetLeftButton() const {
        return m_leftButton;
    }
    
    auto GetRightButton() const {
        return m_rightButton;
    }
    
  private:
    std::shared_ptr<MouseButton> m_leftButton;
    std::shared_ptr<MouseButton> m_rightButton;
    int m_mouseWheelDelta {0};
    Point2 m_motionDelta {0, 0};
};
}
