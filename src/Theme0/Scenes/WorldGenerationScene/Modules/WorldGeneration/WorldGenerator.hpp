/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

namespace JoD {
class WorldArea;

class WorldGenerator {
  public:
    void GenerateWorld();
    
  private:
    void GenerateGrass(std::shared_ptr<WorldArea> WorldArea);
};
}
