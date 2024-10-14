/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

namespace JoD {
class ColorF {
  public:
    SDL_Color ToSDLColor() const;
    
    float r{0.0f};
    float g{0.0f};
    float b{0.0f};
    float a{0.0f};
};
}
