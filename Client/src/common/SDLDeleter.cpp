/*
 * Copyright 2024 Andreas Åkerberg.
 */

#include "SDLDeleter.hpp"

namespace JoD {
void SDLDeleter::operator()(SDL_Window *window) const {
    if (nullptr == window)
        throw std::invalid_argument(
                  CodeLocation() +
                  "window should not be nullptr.");
    SDL_DestroyWindow(window);
}

void SDLDeleter::operator()(SDL_Renderer *renderer) const {
    if (nullptr == renderer)
        throw std::invalid_argument(
                  CodeLocation() +
                  "window should not be nullptr.");
    SDL_DestroyRenderer(renderer);
}

void SDLDeleter::operator()(SDL_Surface *surface) const {
    if (nullptr == surface)
        throw std::invalid_argument(
                  CodeLocation() +
                  "window should not be nullptr.");
    SDL_FreeSurface(surface);
}

void SDLDeleter::operator()(SDL_Texture *texture) const {
    if (nullptr == texture)
        throw std::invalid_argument(
                  CodeLocation() +
                  "window should not be nullptr.");
    SDL_DestroyTexture(texture);
}

void SDLDeleter::operator()(TTF_Font *font) const {
    if (nullptr == font)
        throw std::invalid_argument(
                  CodeLocation() +
                  "window should not be nullptr.");
    TTF_CloseFont(font);
}
}
