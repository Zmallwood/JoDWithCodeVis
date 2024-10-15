/*
 * Copyright 2024 Andreas Åkerberg.
 */
#include "gui_button.hpp"
#include "game/core/input/mouse/mouse_input.hpp"
#include "game/core/input/mouse/mouse_button.hpp"
#include "game/core/engine.hpp"

namespace JoD {
GUIButton::GUIButton(std::string_view text, BoxF area,
                     std::function<void()> action,
                     std::string_view backImageName,
                     std::string_view backHoveredImageName)
  : m_text(text), m_action(action), m_area(area),
  m_backImageName(backImageName),
  m_backHoveredImageName(backHoveredImageName) {
  m_ridButtonImage = _<Engine>().AllocateNewImage();
  m_ridButtonText = _<Engine>().AllocateNewString();
}

void GUIButton::UpdateDerived() {
  auto mousePosition = GetMousePosition();
  if (m_area.Contains(mousePosition)) {
    m_activeBackImage = &m_backHoveredImageName;
    _<Engine>().SetCursorStyle(CursorStyles::Hovering);
    if (_<MouseInput>().GetLeftButton()->HasBeenFiredPickResult())
      m_action();
  }
  else {
    m_activeBackImage = &m_backImageName;
  }
}

void GUIButton::RenderDerived() const {
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
