#pragma once

namespace JoD {
class Tile;

class WorldArea {
  public:
    WorldArea(Size size);
    
    Size GetSize() const;
    
    bool IsValidCoordinate(int x, int y) const;
    
    
    bool IsValidCoordinate(Point2 coordinate) const;
    
    std::shared_ptr<Tile> GetTile(int x, int y) const;
    
    std::shared_ptr<Tile> GetTile(Point2 coordinate) const;
    
  private:
    std::vector<std::vector<std::shared_ptr<Tile>>> m_tiles;
};
}
