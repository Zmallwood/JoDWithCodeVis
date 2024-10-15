/*
 * Copyright 2024 Andreas Åkerberg.
 */
#include "world_generation_scene.hpp"
#include "modules/world_generation/world_generator.hpp"
#include "game/core/scenes_core/scene_engine.hpp"

namespace JoD {
WorldGenerationScene::WorldGenerationScene() {}

void WorldGenerationScene::OnEnterDerived() {
  _<WorldGenerator>().GenerateWorld(_<SceneEngine>().GetWorldAreaSize());
  _<SceneEngine>().GoToScene("MainScene");
}

void WorldGenerationScene::UpdateDerived() {}

void WorldGenerationScene::RenderDerived() const {}
}
