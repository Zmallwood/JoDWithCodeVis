/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "WorldGenerationScene.hpp"
#include "Modules/WorldGeneration/WorldGenerator.hpp"
#include "Game/Core/ScenesCore/SceneManager.hpp"

namespace JoD {
WorldGenerationScene::WorldGenerationScene() {}

void WorldGenerationScene::OnEnterDerived() {
    _<WorldGenerator>().GenerateWorld();
    _<SceneManager>().GoToScene("MainScene");
}

void WorldGenerationScene::UpdateDerived() {}

void WorldGenerationScene::RenderDerived() {}
}
