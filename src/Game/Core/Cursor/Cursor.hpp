#pragma once

#include "CursorStyles.hpp"

namespace JoD {
class Cursor {
  public:
    Cursor();
    
    void Render() const;
    
    void Reset();
    
    void SetCursorStyle(CursorStyles value) {
        m_cursorStyle = value;
    }
    
  private:
    CursorStyles m_cursorStyle {CursorStyles::Normal};
    GLuint m_ridCursorImage{};
    static constexpr float k_cursorSize {0.04f};
};
}
