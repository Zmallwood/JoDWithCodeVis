/*
 * Copyright 2024 Andreas Åkerberg
 */
#include "color_f.hpp"

namespace JoD {
SDL_Color ColorF::ToSDLColor() const {
  return {.r = (unsigned char)(r * 255),
          .g = (unsigned char)(g * 255),
          .b = (unsigned char)(b * 255),
          .a = (unsigned char)(a * 255)};
}
}
