/*
 * Copyright 2024 Andreas Åkerberg
 */
#pragma once
#include "gl_box_f.hpp"
#include "point2_f.hpp"

namespace JoD {
class BoxF {
public:
  GLBoxF ToGLBoxF() const;
  
  Point2F GetCenter() const;
  
  bool Contains(Point2F point) const;
  
  float x{0.0f};
  float y{0.0f};
  float width{0.0f};
  float height{0.0f};
};
}
