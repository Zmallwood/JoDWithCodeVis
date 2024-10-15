#pragma once

#include "game/core/scenes_core/IScene.hpp"

namespace JoD {
class MainMenuScene : public IScene {
  public:
    MainMenuScene();
    
  protected:
    void UpdateDerived() override;
    
    void RenderDerived() const override;
    
  private:
    RID m_ridBackground{0};
    RID m_ridLogo {0};
};
}
