/*
 * Copyright 2024 Andreas Åkerberg.
 */

#include "WorldGenerationScene.hpp"
#include "modules/world_generation/WorldGenerator.hpp"
#include "game/core/scenes_core/SceneEngine.hpp"

namespace JoD {
WorldGenerationScene::WorldGenerationScene() {}

void WorldGenerationScene::OnEnterDerived() {
    _<WorldGenerator>().GenerateWorld(_<SceneEngine>().GetWorldAreaSize());
    _<SceneEngine>().GoToScene("MainScene");
}

void WorldGenerationScene::UpdateDerived() {}

void WorldGenerationScene::RenderDerived() const {}
}
