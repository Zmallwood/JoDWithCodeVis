/*
 * Copyright 2024 Andreas Åkerberg.
 */
#pragma once
#include "game/core/scenes_core/i_scene.hpp"

namespace JoD {
class LoginScene : public IScene {
public:
  LoginScene();
  
protected:
  void UpdateDerived() override;
  
  void RenderDerived() const override;
  
private:
  RID m_ridBackground{0};
  RID m_ridLogo {0};
};
}
