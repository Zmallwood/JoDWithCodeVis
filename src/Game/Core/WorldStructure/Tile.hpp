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
    
  private:
    int m_ground {0};
};
}
