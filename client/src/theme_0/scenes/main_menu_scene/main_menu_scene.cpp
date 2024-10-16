/*
 * Copyright 2024 Andreas Åkerberg.
 */
#include "main_menu_scene.hpp"
#include "game/core/gui_core/gui.hpp"
#include "game/core/gui_core/gui_button.hpp"
#include "game/core/scenes_core/scene_engine.hpp"

namespace JoD {
MainMenuScene::MainMenuScene() {
  m_ridBackground = _<SceneEngine>().AllocateNewImage();
  m_ridLogo = _<SceneEngine>().AllocateNewImage();
  GetGUI()->AddChildComponent(
    std::make_shared<GUIButton>(
      "Login",
      BoxF{0.45f, 0.3f,
           0.1f, 0.05f},
      [] {
        _<SceneEngine>().GoToScene("LoginScene");
      }));
  GetGUI()->AddChildComponent(
    std::make_shared<GUIButton>(
      "Singleplayer sandbox", BoxF{0.45f, 0.37f, 0.1f, 0.05f}, [] {
        _<SceneEngine>().GoToScene("WorldGenerationScene");
      }));
  GetGUI()->AddChildComponent(
    std::make_shared<GUIButton>(
      "Quit",
      BoxF {0.45f, 0.44f,
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
