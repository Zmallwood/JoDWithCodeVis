/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

namespace JoD {
class WorldArea;

class World {
  public:
    World();
    
    auto GetCurrentWorldArea() {
        return m_currentWorldArea;
    }
    
  private:
    std::shared_ptr<WorldArea> m_currentWorldArea;
};
}
