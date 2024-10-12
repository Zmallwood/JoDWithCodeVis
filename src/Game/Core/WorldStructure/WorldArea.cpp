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
}
