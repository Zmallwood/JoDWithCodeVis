/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

namespace JoD {
class Tile;

class WorldArea {
  public:
    WorldArea();
    
  private:
    std::vector<std::vector<std::shared_ptr<Tile>>> m_tiles;
};
}
