/*
 * Copyright 2024 Andreas Åkerberg.
 */
#include "scene_engine.hpp"
#include "game/core/engine.hpp"
#include "theme_0/scenes/intro_scene/intro_scene.hpp"
#include "theme_0/scenes/main_menu_scene/main_menu_scene.hpp"
#include "theme_0/scenes/login_scene/login_scene.hpp"
#include "theme_0/scenes/world_generation_scene/world_generation_scene.hpp"
#include "theme_0/scenes/main_scene/main_scene.hpp"

namespace JoD {
void SceneEngine::AddScene(std::string_view sceneName, IScene& scene) {
  m_scenes.insert({Hash(sceneName), scene});
}

void SceneEngine::InitializeScenes() {
  AddScene("IntroScene", _<IntroScene>());
  AddScene("MainMenuScene", _<MainMenuScene>());
  AddScene("LoginScene", _<LoginScene>());
  AddScene(
    "WorldGenerationScene",
    _<WorldGenerationScene>());
  AddScene("MainScene", _<MainScene>());
}

void SceneEngine::UpdateCurrentScene() {
  if (m_scenes.contains(m_currentScene))
    m_scenes.at(m_currentScene).Update();
}

void SceneEngine::RenderCurrentScene() {
  if (m_scenes.contains(m_currentScene))
    m_scenes.at(m_currentScene).Render();
}

void SceneEngine::GoToScene(std::string_view newSceneName) {
  m_currentScene = Hash(newSceneName);
  if (m_scenes.contains(m_currentScene)) {
    _<Engine>().ResetInputState();
    m_scenes.at(m_currentScene).OnEnter();
  }
}

Size SceneEngine::GetWorldAreaSize() const {
  return _<Engine>().GetWorldAreaSize();
}

RID SceneEngine::AllocateNewImage() const {
  return _<Engine>().AllocateNewImage();
}

void SceneEngine::DrawImage(RID rid, int imageNameHash, const BoxF &area,
                            ColorF color, bool repeatTexture,
                            SizeF textureFillAmount,
                            bool noPixelEffect) const {
  _<Engine>().DrawImage(
    rid, imageNameHash, area, color, repeatTexture,
    textureFillAmount, noPixelEffect);
}

void SceneEngine::DrawImage(RID rid, std::string_view imageName,
                            const BoxF &area,
                            ColorF color, bool repeatTexture,
                            SizeF textureFillAmount,
                            bool noPixelEffect) const {
  _<Engine>().DrawImage(
    rid, imageName, area, color,repeatTexture,
    textureFillAmount, noPixelEffect);
}

RID SceneEngine::AllocateNewString() const {
  return _<Engine>().AllocateNewString();
}

void SceneEngine::DrawString(int id,
                             std::string_view text,
                             Point2F position,
                             ColorF color,
                             bool centerAlign,
                             FontSizes fontSize) const {
  _<Engine>().DrawString(
    id, text, position, color, centerAlign,
    fontSize);
}

RID SceneEngine::AllocateNewTile() const {
  return _<Engine>().AllocateNewTile();
}

bool SceneEngine::AnyMouseButtonIsPressed() const {
  return _<Engine>().AnyMouseButtonisPressed();
}

bool SceneEngine::AnyKeyIsPressed() const {
  return _<Engine>().AnyKeyIsPressed();
}

void SceneEngine::StopEngine() {
  _<Engine>().SetRunning(false);
}
}
