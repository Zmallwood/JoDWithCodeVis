/*
 * Copyright 2024 Andreas Åkerberg.
 */

#include "MainScene.hpp"
#include "modules/world_view_module/WorldView.hpp"
#include "game/core/scenes_core/SceneEngine.hpp"
#include "modules/mouse_rotation_module/MouseRotation.hpp"
#include "modules/KeyboardMovement.hpp"

namespace JoD {
void MainScene::OnEnterDerived() {
    _<WorldView>().Initialize();
}

void MainScene::UpdateDerived() {
    _<MouseRotation>().Update();
    _<KeyboardMovement>().Update();
    _<WorldView>().Update();
}

void MainScene::RenderDerived() const {
    _<WorldView>().Render();
}

Size MainScene::GetWorldAreaSize() const {
    return _<SceneEngine>().GetWorldAreaSize();
}

RID MainScene::AllocateNewTile() const {
    return _<SceneEngine>().AllocateNewTile();
}
}
