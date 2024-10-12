/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "World.hpp"
#include "WorldArea.hpp"

namespace JoD {
World::World()
    : m_currentWorldArea(std::make_shared<WorldArea>()) {}
}
