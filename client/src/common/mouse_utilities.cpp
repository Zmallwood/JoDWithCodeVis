/*
 * Copyright 2024 Andreas Åkerberg.
 */
#include "mouse_utilities.hpp"

namespace JoD {
Point2F GetMousePosition() {
  auto canvasSize = GetCanvasSize();
  int mousePositionPxX;
  int mousePositionPxY;
  SDL_GetMouseState(&mousePositionPxX, &mousePositionPxY);
  auto x = static_cast<float>(mousePositionPxX) / canvasSize.width;
  auto y = static_cast<float>(mousePositionPxY) / canvasSize.height;
  return {x, y};
}
}
