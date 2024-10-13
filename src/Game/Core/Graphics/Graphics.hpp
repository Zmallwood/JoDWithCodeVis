/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

namespace JoD {
class Graphics {
  public:
    Graphics();
    
    void ClearCanvas() const;
    
    void PresentCanvas() const;
    
    auto GetWindow() const {
        return m_window;
    }
    
  private:
    std::shared_ptr<SDL_Window> m_window;
};
}
