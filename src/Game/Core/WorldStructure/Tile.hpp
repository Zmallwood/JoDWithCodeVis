/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

namespace JoD {
class Tile {
  public:
    
    auto GetGround() {
        return m_ground;
    }
    
    void SetGround(int value) {
        m_ground = value;
    }
    
  private:
    int m_ground {0};
};
}
