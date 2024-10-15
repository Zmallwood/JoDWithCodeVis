/*
 * Copyright 2024 Andreas Åkerberg.
 */
#include "CanvasUtilities.hpp"
#include "game/core/graphics/Graphics.hpp"

namespace JoD {
Size GetCanvasSize() {
  int width, height;
  SDL_GetWindowSize(_<Graphics>().GetWindow().get(), &width, &height);
  return {width, height};
}

float GetAspectRatio() {
  auto canvasSize= GetCanvasSize();
  return static_cast<float>(canvasSize.width) / canvasSize.height;
}

float ConvertWidthToHeight(float width) {
  return width * GetAspectRatio();
}

float ConvertHeightToWidth(float height) {
  return height / GetAspectRatio();
}
}
