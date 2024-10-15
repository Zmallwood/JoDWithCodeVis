/*
 * Copyright 2024 Andreas Åkerberg.
 */
#pragma once

#include "GUIComponent.hpp"

namespace JoD {
class GUIButton : public GUIComponent {
public:
  GUIButton(std::string_view text, BoxF area, std::function<void()> action,
            std::string_view backImageName = "GUIDefaultButtonBackground",
            std::string_view backHoveredImageName =
            "GUIDefaultButtonBackgroundHovered");
  
  void UpdateDerived() override;
  
  void RenderDerived() const override;
  
private:
  std::string m_text;
  std::function<void()> m_action;
  RID m_ridButtonImage {0};
  RID m_ridButtonText {0};
  BoxF m_area;
  std::string m_backImageName;
  std::string m_backHoveredImageName;
  std::string* m_activeBackImage {nullptr};
};
}
