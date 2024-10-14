/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "Game/Core/ScenesCore/IScene.hpp"

namespace JoD {
class IntroScene : public IScene {
  public:
    IntroScene();
    
  protected:
    void UpdateDerived() override;
    
    void RenderDerived() const override;
    
  private:
    RID m_ridBackground{0};
    RID m_ridLogo {0};
};
}
