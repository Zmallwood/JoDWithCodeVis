/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "MainScene.hpp"
#include "Modules/WorldViewModule/WorldView.hpp"
#include "Game/Core/ScenesCore/SceneEngine.hpp"
#include "Modules/MouseRotationModule/MouseRotation.hpp"

namespace JoD {
void MainScene::OnEnterDerived() {
    _<WorldView>().Initialize();
}

void MainScene::UpdateDerived() {
    _<MouseRotation>().Update();
    _<WorldView>().Update();
}

void MainScene::RenderDerived() {
    _<WorldView>().Render();
}

Size MainScene::GetWorldAreaSize() {
    return _<SceneEngine>().GetWorldAreaSize();
}

RID MainScene::AllocNewTile() {
    return _<SceneEngine>().AllocNewTile();
}
}
