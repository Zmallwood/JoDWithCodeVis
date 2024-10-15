/*
 * Copyright 2024 Andreas Åkerberg
 */
#include "VertexTile.hpp"

namespace JoD {
VertexTile::VertexTile() {
  v0.uv = {0.0f, 0.0f};
  v1.uv = {1.0f, 0.0f};
  v2.uv = {1.0f, 1.0f};
  v3.uv = {0.0f, 1.0f};
  v0.color = {1.0f, 1.0f, 1.0f, 1.0f};
  v1.color = {1.0f, 1.0f, 1.0f, 1.0f};
  v2.color = {1.0f, 1.0f, 1.0f, 1.0f};
  v3.color = {1.0f, 1.0f, 1.0f, 1.0f};
}
}
