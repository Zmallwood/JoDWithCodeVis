/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

#include "Theme0/Scenes/MainScene/MainScene.hpp"

namespace JoD {
class WorldView {
  public:
    void Initialize();
    
    void Update();
    
    void Render();
    
    Size GetWorldAreaSize();
    
    RID NewTile();
    
  private:
    void DoRenderLoop(std::function<void()> action);
};
}
