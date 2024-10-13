/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

#include "RotationTypes.hpp"

namespace JoD {
class MouseRotation {
  public:
    void Update();
    
  private:
    void UpdateRotationInProgress();
    
    RotationTypes m_currentRotationType {RotationTypes::None};
    
    const float k_rotationSensitivity {1100.0f};
};
}
