/*
 * Copyright 2024 Andreas Åkerberg.
 */

#pragma once

namespace JoD {
class Font {
  public:
    Font(std::string_view fontFileName, int fontSize);
    
    std::shared_ptr<TTF_Font> GetFont() const {
        return m_font;
    }
    
    std::shared_ptr<TTF_Font> GetOutlineFont() const {
        return m_outlineFont;
    }
    
    static constexpr int k_fontOutlineWidth {2};
    
  private:
    std::shared_ptr<TTF_Font> m_font;
    std::shared_ptr<TTF_Font> m_outlineFont;
};
}
