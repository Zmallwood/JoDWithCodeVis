/*
 * Copyright 2024 Andreas Åkerberg
 */
#pragma once
#include "ColorF.hpp"
#include "Point2F.hpp"

namespace JoD {
class Vertex2F {
public:
  Point2F position;
  ColorF color;
  Point2F uv;
};
}
