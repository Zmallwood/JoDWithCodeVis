/*
 * Copyright 2024 Andreas Åkerberg
 */
#pragma once

#include "Game/Core/ScenesCore/IScene.hpp"

namespace JoD {
class MainScene : public IScene {
  public:
    Size GetWorldAreaSize();
    
    RID NewTile();
    
  protected:
    void OnEnterDerived() override;
    
    void UpdateDerived() override;
    
    void RenderDerived() override;
};
}
