/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

namespace JoD {
class Player {
  public:
    void MoveNorth();
    
    void MoveEast();
    
    void MoveSouth();
    
    void MoveWest();
    
    Point3F GetPosition3D() const;
    
    auto GetPosition() const {
        return m_position;
    }
    
    auto GetMajorCoordinate() const {
        return m_majorCoordinate;
    }
    
    auto& GetMovementTimerRef() {
        return m_movementTimer;
    }
    
  private:
    Point2F m_position {0.0f, 0.0f};
    Point3 m_majorCoordinate {0, 0, 0};
    float m_movementSpeed {1.0f};
    Timer m_movementTimer = Timer(m_movementSpeed);
};
}
