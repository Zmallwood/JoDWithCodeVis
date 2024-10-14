/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "GUIComponent.hpp"

namespace JoD {
void GUIComponent::Update() {
    for (auto childComponent : m_childComponents)
        childComponent->Update();
    UpdateDerived();
}

void GUIComponent::Render() const {
    RenderDerived();
    for (auto childComponent : m_childComponents)
        childComponent->Render();
}

void GUIComponent::AddChildComponent(
    std::shared_ptr<GUIComponent> newComponent) {
    if (nullptr == newComponent)
        throw std::invalid_argument(
                  CodeLocation() +
                  "newComponent cannot be nullptr.");
    m_childComponents.push_back(newComponent);
}
}
