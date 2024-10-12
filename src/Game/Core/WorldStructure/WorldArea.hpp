/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

namespace JoD {
class Tile;

class WorldArea {
  public:
    WorldArea();
    
    Size GetSize();
    
    bool IsValidCoordinate(int x, int y);
    
    std::shared_ptr<Tile> GetTile(int x, int y);
    
  private:
    std::vector<std::vector<std::shared_ptr<Tile>>> m_tiles;
};
}
