/*
 * Copyright 2024 Andreas Åkerberg
 */
#pragma once
#include "Point3F.hpp"
#include "Point2F.hpp"
#include "ColorF.hpp"

namespace JoD {
class Vertex3F {
public:
  Point3F position;
  ColorF color;
  Point2F uv;
  Point3F normal;
};
}
