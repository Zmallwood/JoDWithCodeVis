/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

#include "GLBoxF.hpp"
#include "PointF.hpp"

namespace JoD {
class BoxF {
  public:
    GLBoxF ToGLBoxF() const;
    
    PointF GetCenter() const;
    
    bool Contains(PointF point) const;
    
    float x{0.0f};
    float y{0.0f};
    float width{0.0f};
    float height{0.0f};
};
}
