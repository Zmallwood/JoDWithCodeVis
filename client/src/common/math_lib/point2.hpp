/*
 * Copyright 2024 Andreas Åkerberg
 */
#pragma once

namespace JoD {
class Point2 {
public:
  Point2 Translate(int dx, int dy) const;
  
  int x {0};
  int y {0};
};
}
