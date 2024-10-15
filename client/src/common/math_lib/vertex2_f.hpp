/*
 * Copyright 2024 Andreas Åkerberg
 */
#pragma once
#include "color_f.hpp"
#include "point2_f.hpp"

namespace JoD {
class Vertex2F {
public:
  Point2F position;
  ColorF color;
  Point2F uv;
};
}
