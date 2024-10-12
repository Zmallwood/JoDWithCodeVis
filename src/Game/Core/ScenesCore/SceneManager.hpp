#pragma once
#include "IScene.hpp"

namespace JoD {
class SceneManager {
  public:
    SceneManager();
    
    void UpdateCurrentScene();
    
    void RenderCurrentScene();
    
    void GoToScene(std::string_view newSceneName);
    
  private:
    std::map<int, IScene &> m_scenes;
    int m_currentScene{0};
};
}
