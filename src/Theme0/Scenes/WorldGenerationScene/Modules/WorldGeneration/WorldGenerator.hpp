/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

namespace JoD {
class WorldArea;

class WorldGenerator {
  public:
    void GenerateWorld(Size worldAreaSize);
    
  private:
    void CreateRenderingResources(std::shared_ptr<WorldArea> worldArea);
    
    void GenerateGrass(std::shared_ptr<WorldArea> WorldArea);
    
    void CalculateNormals(std::shared_ptr<WorldArea> worldArea);
};
}
