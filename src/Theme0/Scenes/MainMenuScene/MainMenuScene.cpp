/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "MainMenuScene.hpp"
#include "Game/Core/GUICore/GUI.hpp"
#include "Game/Core/GUICore/GUIButton.hpp"
#include "Game/Core/ScenesCore/SceneEngine.hpp"

namespace JoD {
MainMenuScene::MainMenuScene() {
    m_ridBackground = _<SceneEngine>().AllocNewImage();
    m_ridLogo = _<SceneEngine>().AllocNewImage();
    
    GetGUI()->AddChildComponent(
        std::make_shared<GUIButton>(
            "New game", BoxF{0.45f, 0.3f, 0.1f, 0.05f}, [] {
                _<SceneEngine>().GoToScene("WorldGenerationScene");
            }));
    
    GetGUI()->AddChildComponent(
        std::make_shared<GUIButton>(
            "Quit",
            BoxF {0.45f, 0.4f,
                  0.1f, 0.05f}, [] {
                _<SceneEngine>().StopEngine();
            }));
}

void MainMenuScene::UpdateDerived() {}

void MainMenuScene::RenderDerived() const {
    auto areaBackground = BoxF{0.0f, 0.0f, 1.0f, 1.0f};
    _<SceneEngine>().DrawImage(
        m_ridBackground, "DefaultSceneBackground",
        areaBackground);
    
    auto areaLogo = BoxF {0.4, 0.15f, 0.2f, 0.1f};
    _<SceneEngine>().DrawImage(m_ridLogo, "JoDLogo", areaLogo);
}
}
