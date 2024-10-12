/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "IScene.hpp"
#include "Game/Core/GUICore/GUI.hpp"

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

void IScene::Render() {
    RenderDerived();
    m_gui->Render();
}
}
