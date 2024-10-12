/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "SceneEngine.hpp"
#include "Game/Core/Engine.hpp"
#include "Theme0/Scenes/IntroScene/IntroScene.hpp"
#include "Theme0/Scenes/MainMenuScene/MainMenuScene.hpp"
#include "Theme0/Scenes/WorldGenerationScene/WorldGenerationScene.hpp"
#include "Theme0/Scenes/MainScene/MainScene.hpp"

namespace JoD {
void SceneEngine::AddScene(std::string_view sceneName, IScene& scene) {
    m_scenes.insert({Hash(sceneName), scene});
}

void SceneEngine::InitializeScenes() {
    AddScene("IntroScene", _<IntroScene>());
    AddScene("MainMenuScene", _<MainMenuScene>());
    AddScene(
        "WorldGenerationScene",
        _<WorldGenerationScene>());
    AddScene("MainScene", _<MainScene>());
}

void SceneEngine::UpdateCurrentScene() {
    if (m_scenes.contains(m_currentScene)) {
        m_scenes.at(m_currentScene).Update();
    }
}

void SceneEngine::RenderCurrentScene() {
    if (m_scenes.contains(m_currentScene)) {
        m_scenes.at(m_currentScene).Render();
    }
}

void SceneEngine::GoToScene(std::string_view newSceneName) {
    m_currentScene = Hash(newSceneName);
    
    if (m_scenes.contains(m_currentScene)) {
        m_scenes.at(m_currentScene).OnEnter();
    }
}

RID SceneEngine::NewImage() {
    return _<Engine>().NewImage();
}

void SceneEngine::DrawImage(RID rid, int imageNameHash, const BoxF &area,
                            ColorF color, bool repeatTexture,
                            SizeF textureFillAmount,
                            bool noPixelEffect) {
    _<Engine>().DrawImage(
        rid, imageNameHash, area, color, repeatTexture,
        textureFillAmount, noPixelEffect);
}

void SceneEngine::DrawImage(RID rid, std::string_view imageName,
                            const BoxF &area,
                            ColorF color, bool repeatTexture,
                            SizeF textureFillAmount,
                            bool noPixelEffect) {
    _<Engine>().DrawImage(
        rid, imageName, area, color,repeatTexture,
        textureFillAmount, noPixelEffect);
}

RID SceneEngine::NewString() {
    return _<Engine>().NewString();
}

void SceneEngine::DrawString(int id,
                             std::string_view text,
                             Point2F position,
                             ColorF color,
                             bool centerAlign,
                             FontSizes fontSize) {
    _<Engine>().DrawString(
        id, text, position, color, centerAlign,
        fontSize);
}

void SceneEngine::StopEngine() {
    _<Engine>().SetRunning(false);
}
}
