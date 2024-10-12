/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "WorldView.hpp"
#include "Game/Core/Graphics/Rendering/GroundRendering/GroundRenderer.hpp"
#include "SubPainters/GroundSurfacePainter.hpp"

namespace JoD {
WorldView::WorldView() {}

void WorldView::Update() {}

void WorldView::Render() {
    _<GroundRenderer>().StartBatchDrawing();
    DoRenderLoop(
        [] {
            _<GroundSurfacePainter>().Paint();
        });
    _<GroundRenderer>().StopBatchDrawing();
}

void WorldView::DoRenderLoop(std::function<void()> action) {}
}
