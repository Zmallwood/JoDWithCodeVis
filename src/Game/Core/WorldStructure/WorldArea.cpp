/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "WorldArea.hpp"
#include "Game/Core/Configuration/GameProperties.hpp"
#include "Tile.hpp"

namespace JoD {
WorldArea::WorldArea() {
    auto size = _<GameProperties>().GetWorldAreaSize();
    
    for (auto x = 0; x < size.width; x++) {
        m_tiles.push_back(std::vector<std::shared_ptr<Tile>>());
        
        for (auto y = 0; y < size.height; y++) {
            m_tiles.at(x).push_back(std::make_shared<Tile>());
        }
    }
}

Size WorldArea::GetSize() {
    if (m_tiles.size() > 0) {
        return {static_cast<int>(m_tiles.size()),
                static_cast<int>(m_tiles.at(0).size())};
    }
    return {0, 0};
}

bool WorldArea::IsValidCoordinate(int x, int y) {
    auto size = GetSize();
    return x >= 0 && y >= 0 && x < size.width && y < size.height;
}

std::shared_ptr<Tile> WorldArea::GetTile(int x, int y) {
    if (IsValidCoordinate(x, y)) {
        return m_tiles.at(x).at(y);
    }
    return nullptr;
}
}
