/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "IntroScene.hpp"
#include "Game/Core/Input/Keyboard/KeyboardInput.hpp"
#include "Game/Core/Input/Mouse/MouseInput.hpp"
#include "Game/Core/ScenesCore/SceneManager.hpp"

namespace JoD {
IntroScene::IntroScene() {
    m_ridBackground = _<SceneManager>().NewImage();
    m_ridLogo = _<SceneManager>().NewImage();
}

void IntroScene::UpdateDerived() {
    if (_<KeyboardInput>().AnyKeyIsPressed() ||
        _<MouseInput>().AnyButtonIsPressed()) {
        _<SceneManager>().GoToScene("MainMenuScene");
    }
}

void IntroScene::RenderDerived() {
    auto areaBackground = BoxF{0.0f, 0.0f, 1.0f, 1.0f};
    _<SceneManager>().DrawImage(
        m_ridBackground, "DefaultSceneBackground",
        areaBackground);
    
    auto areaLogo = BoxF {0.3, 0.2f, 0.4f, 0.2f};
    _<SceneManager>().DrawImage(m_ridLogo, "JoDLogo", areaLogo);
}
}
