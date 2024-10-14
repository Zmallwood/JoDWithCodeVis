#include "World.hpp"
#include "WorldArea.hpp"

namespace JoD {
void World::EnsureCreated(Size worldAreaSize) {
    if (!m_currentWorldArea)
        m_currentWorldArea = std::make_shared<WorldArea>(worldAreaSize);
}
}
