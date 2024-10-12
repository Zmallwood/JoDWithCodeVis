/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

#include "Game/Core/ScenesCore/IScene.hpp"

namespace JoD {
class WorldGenerationScene : public IScene {
  public:
    WorldGenerationScene();
    
  protected:
    void UpdateDerived() override;
    
    void RenderDerived() override;
    
  private:
    RID m_ridBackground {0};
    RID m_progressText {0};
};
}
