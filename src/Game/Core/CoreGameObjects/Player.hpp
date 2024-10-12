/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

namespace JoD {
class Player {
  public:
    Point3F GetPosition3D();
    
    auto GetPosition() {
        return m_position;
    }
    
    auto GetMajorCoordinate() {
        return m_majorCoordinate;
    }
    
  private:
    Point2F m_position {0.0f, 0.0f};
    Point3 m_majorCoordinate {0, 0, 0};
};
}
