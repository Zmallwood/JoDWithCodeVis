/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

namespace JoD {
class Font;

class TextRenderer {
  public:
    TextRenderer();
    
    RID AllocNewString();
    
    void DrawString(int id,
                    std::string_view text,
                    Point2F position,
                    ColorF color = Colors::White,
                    bool centerAlign= false,
                    FontSizes fontSize= FontSizes::_20) const;
    
    SizeF MeasureString(std::string_view text, FontSizes font_size) const;
    
  private:
    void RenderText(int id,
                    std::string_view text,
                    ColorF color,
                    bool centerAlign,
                    FontSizes font_size,
                    std::string &out_uniqueNameID,
                    SizeF &out_size) const;
    
    const std::string k_relativeFontsPath = "Resources/Fonts/";
    const ColorF k_outlineColor {Colors::TransparentBlack};
    std::map<FontSizes, std::shared_ptr<Font>> m_fonts {};
    std::map<int, std::string> m_uniqueNameIDs {};
    std::map<int, RID> m_rids {};
};
}
