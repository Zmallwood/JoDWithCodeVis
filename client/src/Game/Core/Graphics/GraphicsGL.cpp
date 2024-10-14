#include "GraphicsGL.hpp"

namespace JoD {
GraphicsGL::GraphicsGL() {
    glewExperimental = GL_TRUE;
    auto glewError = glewInit();
    if (glewError != GLEW_OK)
        printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
    if (SDL_GL_SetSwapInterval(0) < 0)
        printf(
            "Warning: Unable to disable VSync! SDL Error: %s\n",
            SDL_GetError());
    glClearColor(
        k_clearColor.r, k_clearColor.g, k_clearColor.b,
        k_clearColor.a);
    if (k_cullFace) {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
    }
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
}
