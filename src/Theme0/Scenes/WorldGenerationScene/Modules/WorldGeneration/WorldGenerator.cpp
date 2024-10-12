/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "WorldGenerator.hpp"
#include "Game/Core/WorldStructure/World.hpp"
#include "Game/Core/WorldStructure/WorldArea.hpp"
#include "Game/Core/WorldStructure/Tile.hpp"

namespace JoD {
void WorldGenerator::GenerateWorld(Size worldAreaSize) {
    _<World>().EnsureCreated(worldAreaSize);
    auto worldArea = _<World>().GetCurrentWorldArea();
    GenerateGrass(worldArea);
}

void WorldGenerator::GenerateGrass(std::shared_ptr<WorldArea> worldArea) {
    auto size = worldArea->GetSize();
    
    for (auto y = 0; y < size.height; y++) {
        for (auto x = 0; x < size.width; x++) {
            auto tile = worldArea->GetTile(x, y);
            if (tile) {
                tile->SetGround("GroundGrass");
            }
        }
    }
}
}
