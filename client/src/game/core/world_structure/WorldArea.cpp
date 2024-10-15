#include "WorldArea.hpp"
#include "Tile.hpp"

namespace JoD {
WorldArea::WorldArea(Size size) {
    for (auto x = 0; x < size.width; x++) {
        m_tiles.push_back(std::vector<std::shared_ptr<Tile>>());
        for (auto y = 0; y < size.height; y++)
            m_tiles.at(x).push_back(std::make_shared<Tile>());
    }
}

Size WorldArea::GetSize() const {
    if (m_tiles.size() > 0)
        return {static_cast<int>(m_tiles.size()),
                static_cast<int>(m_tiles.at(0).size())};
    return {0, 0};
}

bool WorldArea::IsValidCoordinate(int x, int y) const {
    auto size = GetSize();
    return x >= 0 && y >= 0 && x < size.width && y < size.height;
}

bool WorldArea::IsValidCoordinate(Point2 coordinate) const {
    return IsValidCoordinate(coordinate.x, coordinate.y);
}

std::shared_ptr<Tile> WorldArea::GetTile(int x, int y) const {
    if (IsValidCoordinate(x, y))
        return m_tiles.at(x).at(y);
    throw std::invalid_argument(
              CodeLocation() +
              "x or y does not correspond to a valid tile coordinate.");
}

std::shared_ptr<Tile> WorldArea::GetTile(Point2 coordinate) const {
    return GetTile(coordinate.x, coordinate.y);
}
}
