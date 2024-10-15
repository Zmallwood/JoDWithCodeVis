/*
 * Copyright 2024 Andreas Åkerberg.
 */
#include "main_scene.hpp"
#include "modules/world_view_module/world_view.hpp"
#include "game/core/scenes_core/scene_engine.hpp"
#include "modules/mouse_rotation_module/mouse_rotation.hpp"
#include "modules/keyboard_movement.hpp"

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
