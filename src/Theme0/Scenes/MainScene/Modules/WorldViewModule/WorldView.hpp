/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

namespace JoD {
class WorldView {
  public:
    WorldView();
    
    void Update();
    
    void Render();
    
  private:
    void DoRenderLoop(std::function<void()> action);
};
}
