/*
 * Copyright 2024 Andreas Åkerberg.
 */

#pragma once

namespace JoD {
class Graphics {
  public:
    Graphics();
    
    void ClearCanvas() const;
    
    void PresentCanvas() const;
    
    GLuint GetImage(int imageNameHash) const;
    
    GLuint GetImage(std::string_view imageName) const;
    
    void CreateBlankImage(std::string uniqueImageName) const;
    
    auto GetWindow() const {
        return m_window;
    }
    
  private:
    std::shared_ptr<SDL_Window> m_window;
};
}
