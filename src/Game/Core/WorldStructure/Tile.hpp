/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

namespace JoD {
class Tile {
  public:
    void SetGround(std::string_view groundName);
    
    auto GetGround() {
        return m_ground;
    }
    
    auto GetElevation() {
        return m_elevation;
    }
    
  private:
    int m_ground {0};
    float m_elevation {0.0f};
};
}
