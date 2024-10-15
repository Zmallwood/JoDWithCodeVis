/*
 * Copyright 2024 Andreas Åkerberg
 */
#pragma once
#include "point3_f.hpp"
#include "point2_f.hpp"
#include "color_f.hpp"

namespace JoD {
class Vertex3F {
public:
  Point3F position;
  ColorF color;
  Point2F uv;
  Point3F normal;
};
}
