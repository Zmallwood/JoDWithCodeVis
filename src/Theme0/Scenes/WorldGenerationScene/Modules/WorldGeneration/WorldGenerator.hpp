/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

namespace JoD {
class WorldArea;

class WorldGenerator {
  public:
    void GenerateWorld(Size worldAreaSize) const;
    
  private:
    void CreateRenderingResources(std::shared_ptr<WorldArea> worldArea) const;
    
    void GenerateGrass(std::shared_ptr<WorldArea> WorldArea) const;
    
    void CalculateNormals(std::shared_ptr<WorldArea> worldArea) const;
};
}
