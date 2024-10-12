/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "MouseUtilities.hpp"
#include "CanvasUtilities.hpp"

namespace JoD {
PointF GetMousePosition() {
    auto canvasSize = GetCanvasSize();
    int mousePositionPxX;
    int mousePositionPxY;
    SDL_GetMouseState(&mousePositionPxX, &mousePositionPxY);
    auto x = static_cast<float>(mousePositionPxX) / canvasSize.width;
    auto y = static_cast<float>(mousePositionPxY) / canvasSize.height;
    return {x, y};
}
}
