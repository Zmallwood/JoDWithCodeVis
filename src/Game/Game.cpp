/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "Game.hpp"
#include "Core/Engine.hpp"
#include "Core/Configuration/GameProperties.hpp"
#include "Core/ScenesCore/SceneManager.hpp"
#include "Theme0/Scenes/IntroScene/IntroScene.hpp"
#include "Theme0/Scenes/MainMenuScene/MainMenuScene.hpp"
#include "Theme0/Scenes/WorldGenerationScene/WorldGenerationScene.hpp"
#include "Theme0/Scenes/MainScene/MainScene.hpp"

namespace JoD {
void Game::Start() {
    _<Engine>();
    _<SceneManager>().AddScene("IntroScene", _<IntroScene>());
    _<SceneManager>().AddScene("MainMenuScene", _<MainMenuScene>());
    _<SceneManager>().AddScene(
        "WorldGenerationScene",
        _<WorldGenerationScene>());
    _<SceneManager>().AddScene("MainScene", _<MainScene>());
    _<SceneManager>().GoToScene("IntroScene");
    _<GameProperties>().SetWorldAreaSize({140, 100});
    _<Engine>().Run();
}
}
