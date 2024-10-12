/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "SceneManager.hpp"
#include "Game/Core/Engine.hpp"

namespace JoD {
void SceneManager::AddScene(std::string_view sceneName, IScene& scene) {
    m_scenes.insert({Hash(sceneName), scene});
}

void SceneManager::UpdateCurrentScene() {
    if (m_scenes.contains(m_currentScene)) {
        m_scenes.at(m_currentScene).Update();
    }
}

void SceneManager::RenderCurrentScene() {
    if (m_scenes.contains(m_currentScene)) {
        m_scenes.at(m_currentScene).Render();
    }
}

void SceneManager::GoToScene(std::string_view newSceneName) {
    m_currentScene = Hash(newSceneName);
    
    if (m_scenes.contains(m_currentScene)) {
        m_scenes.at(m_currentScene).OnEnter();
    }
}

RID SceneManager::NewImage() {
    return _<Engine>().NewImage();
}

void SceneManager::DrawImage(RID rid, int imageNameHash, const BoxF &area,
                             ColorF color, bool repeatTexture,
                             SizeF textureFillAmount,
                             bool noPixelEffect) {
    _<Engine>().DrawImage(
        rid, imageNameHash, area, color, repeatTexture,
        textureFillAmount, noPixelEffect);
}

void SceneManager::DrawImage(RID rid, std::string_view imageName,
                             const BoxF &area,
                             ColorF color, bool repeatTexture,
                             SizeF textureFillAmount,
                             bool noPixelEffect) {
    _<Engine>().DrawImage(
        rid, imageName, area, color,repeatTexture,
        textureFillAmount, noPixelEffect);
}

RID SceneManager::NewString() {
    return _<Engine>().NewString();
}

void SceneManager::DrawString(int id,
                              std::string_view text,
                              Point2F position,
                              ColorF color,
                              bool centerAlign,
                              FontSizes fontSize) {
    _<Engine>().DrawString(
        id, text, position, color, centerAlign,
        fontSize);
}
}
