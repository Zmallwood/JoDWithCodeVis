/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "WorldGenerationScene.hpp"
#include "Modules/WorldGeneration/WorldGenerator.hpp"
#include "Game/Core/ScenesCore/SceneEngine.hpp"

namespace JoD {
WorldGenerationScene::WorldGenerationScene() {}

void WorldGenerationScene::OnEnterDerived() {
    _<WorldGenerator>().GenerateWorld();
    _<SceneEngine>().GoToScene("MainScene");
}

void WorldGenerationScene::UpdateDerived() {}

void WorldGenerationScene::RenderDerived() {}
}
