/*
 * Copyright 2024 Andreas Åkerberg.
 */
#pragma once
#include "game/core/scenes_core/i_scene.hpp"

namespace JoD {
class MainScene : public IScene {
public:
  Size GetWorldAreaSize() const;
  
  RID AllocateNewTile() const;
  
protected:
  void OnEnterDerived() override;
  
  void UpdateDerived() override;
  
  void RenderDerived() const override;
};
}
