/*
 * Copyright 2024 Andreas Åkerberg.
 */
#include "i_scene.hpp"
#include "game/core/gui_core/gui.hpp"

namespace JoD {
IScene::IScene()
  : m_gui(std::make_shared<GUI>()) {}

void IScene::OnEnter() {
  OnEnterDerived();
}

void IScene::Update() {
  m_gui->Update();
  UpdateDerived();
}

void IScene::Render() const {
  RenderDerived();
  m_gui->Render();
}
}
