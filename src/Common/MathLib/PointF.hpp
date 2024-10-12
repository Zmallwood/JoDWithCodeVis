/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

namespace JoD {
class PointF {
  public:
    PointF Translate(float dx, float dy) const;
    
    float x{0.0f};
    float y{0.0f};
};
}
