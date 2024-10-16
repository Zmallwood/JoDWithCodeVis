/*
 * Copyright 2024 Andreas Åkerberg.
 */
#include "graphics.hpp"
#include "graphics_gl.hpp"
#include "game/core/assets/images/image_bank.hpp"

namespace JoD {
Graphics::Graphics() {
  m_window = std::shared_ptr<SDL_Window>(
    SDL_CreateWindow(
      "Journey of Dreams", SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED, 660, 660,
      SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN |
      SDL_WINDOW_FULLSCREEN_DESKTOP),
    SDLDeleter());
  if (m_window == nullptr) {
    std::cout << "Window could not be created! SDL Error: "
              << std::string(SDL_GetError()) << std::endl;
    return;
  }
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
  if (SDL_GL_CreateContext(m_window.get()) == nullptr) {
    std::cout << "OpenGL context could not be created! SDL Error: "
              << std::string(SDL_GetError()) << std::endl;
    return;
  }
  _<GraphicsGL>();
}

void Graphics::ClearCanvas() const {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Graphics::PresentCanvas() const {
  SDL_GL_SwapWindow(m_window.get());
}

GLuint Graphics::GetImage(int imageNameHash) const {
  return _<ImageBank>().GetImage(imageNameHash);
}

GLuint Graphics::GetImage(std::string_view imageName) const {
  return _<ImageBank>().GetImage(imageName);
}

void Graphics::CreateBlankImage(std::string uniqueImageName) const {
  _<ImageBank>().CreateBlankImage(uniqueImageName);
}
}
