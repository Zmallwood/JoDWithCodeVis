/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "WorldView.hpp"
#include "Game/Core/Graphics/Rendering/GroundRendering/GroundRenderer.hpp"
#include "SubPainters/GroundSurfacePainter.hpp"
#include "Camera.hpp"

namespace JoD {
void WorldView::Initialize() {
    _<GroundSurfacePainter>().Initialize();
}

void WorldView::Update() {
    _<Camera>().Update();
}

void WorldView::Render() {
    _<GroundRenderer>().StartBatchDrawing();
    DoRenderLoop(
        [] {
            _<GroundSurfacePainter>().Paint();
        });
    _<GroundRenderer>().StopBatchDrawing();
}

void WorldView::DoRenderLoop(std::function<void()> action) {
    action();
}

Size WorldView::GetWorldAreaSize() {
    return _<MainScene>().GetWorldAreaSize();
}

RID WorldView::NewTile() {
    return _<MainScene>().NewTile();
}
}
