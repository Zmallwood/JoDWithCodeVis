/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

namespace JoD {
class Player {
  public:
    Point3F GetPosition3D();
    
  private:
    Point2F m_position {0.0f, 0.0f};
};
}
