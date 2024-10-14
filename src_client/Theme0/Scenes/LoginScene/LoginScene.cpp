/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "LoginScene.hpp"
#include "Game/Core/ScenesCore/SceneEngine.hpp"
#include "Game/Core/GUICore/GUI.hpp"
#include "Game/Core/GUICore/GUIButton.hpp"
#include "Modules/LoginAttempter.hpp"

namespace JoD {
LoginScene::LoginScene() {
    m_ridBackground = _<SceneEngine>().AllocateNewImage();
    m_ridLogo = _<SceneEngine>().AllocateNewImage();
    GetGUI()->AddChildComponent(
        std::make_shared<GUIButton>(
            "Login", BoxF{0.52f, 0.57f, 0.07f, 0.05f}, [] {
                auto loginSuccessful = _<LoginAttempter>().AttemptLogin();
                
                if (loginSuccessful)
                    _<SceneEngine>().GoToScene("WorldGenerationScene");
            }));
    GetGUI()->AddChildComponent(
        std::make_shared<GUIButton>(
            "Back", BoxF{0.42f, 0.57f, 0.07f, 0.05f}, [] {
                _<SceneEngine>().GoToScene("MainMenuScene");
            }));
}

void LoginScene::UpdateDerived() {}

void LoginScene::RenderDerived() const {
    auto areaBackground = BoxF{0.0f, 0.0f, 1.0f, 1.0f};
    _<SceneEngine>().DrawImage(
        m_ridBackground, "DefaultSceneBackground",
        areaBackground);
    auto areaLogo = BoxF {0.4, 0.15f, 0.2f, 0.1f};
    _<SceneEngine>().DrawImage(m_ridLogo, "JoDLogo", areaLogo);
}
}
