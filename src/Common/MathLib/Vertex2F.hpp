#pragma once

#include "ColorF.hpp"
#include "PointF.hpp"

namespace JoD {
class Vertex2F {
  public:
    PointF position;
    ColorF color;
    PointF uv;
};
}
