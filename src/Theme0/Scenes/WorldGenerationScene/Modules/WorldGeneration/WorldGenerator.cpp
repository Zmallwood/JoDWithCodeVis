/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "WorldGenerator.hpp"
#include "Game/Core/WorldStructure/World.hpp"
#include "Game/Core/WorldStructure/WorldArea.hpp"

namespace JoD {
void WorldGenerator::GenerateWorld() {
    auto worldArea = _<World>().GetCurrentWorldArea();
    GenerateGrass(worldArea);
}

void WorldGenerator::GenerateGrass(std::shared_ptr<WorldArea> worldArea) {}
}
