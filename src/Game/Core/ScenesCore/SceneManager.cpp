#include "SceneManager.hpp"
#include "Theme0/Scenes/IntroScene/IntroScene.hpp"
#include "Theme0/Scenes/MainMenuScene/MainMenuScene.hpp"
#include "Theme0/Scenes/MainScene/MainScene.hpp"

namespace JoD {
SceneManager::SceneManager() {
    m_scenes.insert({Hash("IntroScene"), _<IntroScene>()});
    m_scenes.insert({Hash("MainMenuScene"), _<MainMenuScene>()});
    m_scenes.insert({Hash("MainScene"), _<MainScene>()});
    
    m_currentScene = Hash("IntroScene");
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
}
}
