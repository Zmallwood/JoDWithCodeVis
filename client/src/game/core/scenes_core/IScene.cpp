#include "IScene.hpp"
#include "game/core/gui_core/GUI.hpp"

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
