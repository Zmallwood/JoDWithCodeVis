#pragma once

#include "FontSizes.hpp"

namespace JoD {
class Font;

class TextRenderer {
  public:
    TextRenderer();
    
    void RenderText(int id,
                    std::string_view text,
                    ColorF color,
                    bool centerAlign,
                    FontSizes font_size,
                    std::string &out_uniqueNameID,
                    SizeF &out_size) const;
    
    int NewString();
    
    void DrawString(int id,
                    std::string_view text,
                    PointF position,
                    ColorF color = Colors::White,
                    bool centerAlign= false,
                    FontSizes fontSize= FontSizes::_20);
    
    SizeF MeasureString(std::string_view text, FontSizes font_size) const;
    
  private:
    const std::string k_relativeFontsPath = "Resources/Fonts/";
    const ColorF k_outlineColor {Colors::TransparentBlack};
    std::map<FontSizes, std::shared_ptr<Font>> m_fonts {};
    std::map<int, std::string> m_uniqueNameIDs {};
    std::map<int, RID> m_rids {};
};
}
