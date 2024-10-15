#pragma once

#include "game/core/scenes_core/IScene.hpp"

namespace JoD {
class WorldGenerationScene : public IScene {
  public:
    WorldGenerationScene();
    
  protected:
    void OnEnterDerived() override;
    
    void UpdateDerived() override;
    
    void RenderDerived() const override;
    
  private:
    RID m_ridBackground {0};
    RID m_progressText {0};
};
}
