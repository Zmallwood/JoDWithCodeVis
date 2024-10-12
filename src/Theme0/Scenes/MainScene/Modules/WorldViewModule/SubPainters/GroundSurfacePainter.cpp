/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "GroundSurfacePainter.hpp"
#include "Theme0/Scenes/MainScene/Modules/WorldViewModule/WorldView.hpp"

namespace JoD {
void GroundSurfacePainter::Initialize() {
    auto worldAreaSize = _<WorldView>().GetWorldAreaSize();
    
    for (auto y = 0; y < worldAreaSize.height; y++)
        for (auto x = 0; x < worldAreaSize.width; x++)
            m_ridsTileLayers[x][y] = _<WorldView>().NewTile();
}

void GroundSurfacePainter::Paint() {}
}
