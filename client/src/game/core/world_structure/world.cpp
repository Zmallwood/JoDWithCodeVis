/*
 * Copyright 2024 Andreas Åkerberg.
 */
#include "world.hpp"
#include "world_area.hpp"

namespace JoD {
void World::EnsureCreated(Size worldAreaSize) {
  if (!m_currentWorldArea)
    m_currentWorldArea = std::make_shared<WorldArea>(worldAreaSize);
}
}
