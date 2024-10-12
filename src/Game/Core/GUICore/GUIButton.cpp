/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "GUIButton.hpp"
#include "Game/Core/Graphics/Rendering/ImageRendering/ImageRenderer.hpp"
#include "Game/Core/Graphics/Rendering/TextRendering/TextRenderer.hpp"
#include "Game/Core/Cursor/Cursor.hpp"
#include "Game/Core/Input/Mouse/MouseInput.hpp"
#include "Game/Core/Input/Mouse/MouseButton.hpp"

namespace JoD {
GUIButton::GUIButton(std::string_view text, BoxF area,
                     std::function<void()> action,
                     std::string_view backImageName,
                     std::string_view backHoveredImageName)
    : m_text(text), m_action(action), m_area(area),
    m_backImageName(backImageName),
    m_backHoveredImageName(backHoveredImageName) {
    m_ridButtonImage = _<ImageRenderer>().NewImage();
    m_ridButtonText = _<TextRenderer>().NewString();
}

void GUIButton::UpdateDerived() {
    auto mousePosition = GetMousePosition();
    
    if (m_area.Contains(mousePosition)) {
        m_activeBackImage = &m_backHoveredImageName;
        _<Cursor>().SetCursorStyle(CursorStyles::Hovering);
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
    
    _<ImageRenderer>().DrawImage(
        m_ridButtonImage, Hash(*m_activeBackImage),
        m_area);
    _<TextRenderer>().DrawString(
        m_ridButtonText, m_text, m_area.GetCenter(),
        Colors::White, true);
}
}
