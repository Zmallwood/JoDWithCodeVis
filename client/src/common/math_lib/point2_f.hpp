/*
 * Copyright 2024 Andreas Åkerberg
 */
#pragma once
#include "point2.hpp"

namespace JoD {
class Point2F {
public:
  Point2F Translate(float dx, float dy) const;
  
  Point2 ToIntPoint() const;
  
  float x{0.0f};
  float y{0.0f};
};
}
