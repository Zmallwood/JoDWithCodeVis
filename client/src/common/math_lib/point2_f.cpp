/*
 * Copyright 2024 Andreas Åkerberg
 */
#include "point2_f.hpp"

namespace JoD {
Point2F Point2F::Translate(float dx, float dy) const {
  return {x + dx, y + dy};
}

Point2 Point2F::ToIntPoint() const {
  return {static_cast<int>(x), static_cast<int>(y)};
}
}
