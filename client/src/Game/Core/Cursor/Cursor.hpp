#pragma once

namespace JoD {
class Cursor {
  public:
    Cursor();
    
    void Render() const;
    
    void Reset();
    
    void HideThisFrame();
    
    void SetCursorStyle(CursorStyles value) {
        m_cursorStyle = value;
    }
    
  private:
    CursorStyles m_cursorStyle {CursorStyles::Normal};
    GLuint m_ridCursorImage{0};
    bool m_visibleThisFrame {true};
    
    static constexpr float k_cursorSize {0.04f};
};
}
