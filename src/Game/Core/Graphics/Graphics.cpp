/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "Graphics.hpp"

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
    
    glewExperimental = GL_TRUE;
    auto glew_error = glewInit();
    if (glew_error != GLEW_OK)
        printf("Error initializing GLEW! %s\n", glewGetErrorString(glew_error));
    if (SDL_GL_SetSwapInterval(0) < 0)
        printf(
            "Warning: Unable to disable VSync! SDL Error: %s\n",
            SDL_GetError());
    glClearColor(0.0f, 0.65f, 1.0f, 1.0f);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Graphics::ClearCanvas() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Graphics::PresentCanvas() {
    SDL_GL_SwapWindow(m_window.get());
}
}
