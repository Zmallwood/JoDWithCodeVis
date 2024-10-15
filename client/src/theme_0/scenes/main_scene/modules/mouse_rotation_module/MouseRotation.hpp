/*
 * Copyright 2024 Andreas Åkerberg.
 */

#pragma once

namespace JoD {
class MouseRotation {
  public:
    void Update();
    
  private:
    void UpdateRotationInProgress() const;
    
    RotationTypes m_currentRotationType {RotationTypes::None};
    
    const float k_rotationSensitivity {1100.0f};
};
}
