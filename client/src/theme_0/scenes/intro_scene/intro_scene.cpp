/*
 * Copyright 2024 Andreas Åkerberg.
 */
#include "intro_scene.hpp"
#include "game/core/scenes_core/scene_engine.hpp"

namespace JoD {
IntroScene::IntroScene() {
  m_ridBackground = _<SceneEngine>().AllocateNewImage();
  m_ridLogo = _<SceneEngine>().AllocateNewImage();
}

void IntroScene::UpdateDerived() {
  if (_<SceneEngine>().AnyKeyIsPressed() ||
      _<SceneEngine>().AnyMouseButtonIsPressed()) {
    _<SceneEngine>().GoToScene("MainMenuScene");
  }
}

void IntroScene::RenderDerived() const {
  auto areaBackground = BoxF{0.0f, 0.0f, 1.0f, 1.0f};
  _<SceneEngine>().DrawImage(
    m_ridBackground, "DefaultSceneBackground",
    areaBackground);
  auto areaLogo = BoxF {0.3, 0.2f, 0.4f, 0.2f};
  _<SceneEngine>().DrawImage(m_ridLogo, "JoDLogo", areaLogo);
}
}
