/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "GUIButton.hpp"
#include "Game/Core/Input/Mouse/MouseInput.hpp"
#include "Game/Core/Input/Mouse/MouseButton.hpp"
#include "Game/Core/Engine.hpp"

namespace JoD {
GUIButton::GUIButton(std::string_view text, BoxF area,
                     std::function<void()> action,
                     std::string_view backImageName,
                     std::string_view backHoveredImageName)
    : m_text(text), m_action(action), m_area(area),
    m_backImageName(backImageName),
    m_backHoveredImageName(backHoveredImageName) {
    m_ridButtonImage = _<Engine>().AllocNewImage();
    m_ridButtonText = _<Engine>().AllocNewString();
}

void GUIButton::UpdateDerived() {
    auto mousePosition = GetMousePosition();
    
    if (m_area.Contains(mousePosition)) {
        m_activeBackImage = &m_backHoveredImageName;
        _<Engine>().SetCursorStyle(CursorStyles::Hovering);
        if (_<MouseInput>().GetLeftButton()->GetIsPressed()) {
            m_action();
        }
    }
    else {
        m_activeBackImage = &m_backImageName;
    }
}

void GUIButton::RenderDerived() {
    if (!m_activeBackImage)
        return;
    
    _<Engine>().DrawImage(
        m_ridButtonImage, Hash(*m_activeBackImage),
        m_area);
    _<Engine>().DrawString(
        m_ridButtonText, m_text, m_area.GetCenter(),
        Colors::White, true);
}
}
