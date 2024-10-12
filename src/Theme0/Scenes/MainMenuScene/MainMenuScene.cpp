/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "MainMenuScene.hpp"
#include "Game/Core/GUICore/GUI.hpp"
#include "Game/Core/GUICore/GUIButton.hpp"
#include "Game/Core/ScenesCore/SceneManager.hpp"
#include "Game/Core/Engine.hpp"

namespace JoD {
MainMenuScene::MainMenuScene() {
    m_ridBackground = _<SceneManager>().NewImage();
    m_ridLogo = _<SceneManager>().NewImage();
    
    GetGUI()->AddChildComponent(
        std::make_shared<GUIButton>(
            "New game", BoxF{0.45f, 0.3f, 0.1f, 0.05f}, [] {
                _<SceneManager>().GoToScene("WorldGenerationScene");
            }));
    
    GetGUI()->AddChildComponent(
        std::make_shared<GUIButton>(
            "Quit",
            BoxF {0.45f, 0.4f,
                  0.1f, 0.05f}, [] {
                _<Engine>().
                SetRunning(false);
            }));
}

void MainMenuScene::UpdateDerived() {}

void MainMenuScene::RenderDerived() {
    auto areaBackground = BoxF{0.0f, 0.0f, 1.0f, 1.0f};
    _<SceneManager>().DrawImage(
        m_ridBackground, "DefaultSceneBackground",
        areaBackground);
    
    auto areaLogo = BoxF {0.4, 0.15f, 0.2f, 0.1f};
    _<SceneManager>().DrawImage(m_ridLogo, "JoDLogo", areaLogo);
}
}
