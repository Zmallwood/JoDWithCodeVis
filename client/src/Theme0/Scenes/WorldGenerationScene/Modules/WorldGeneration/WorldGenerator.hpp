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
    
    void GenerateGrass(std::shared_ptr<WorldArea> worldArea) const;
    
    void GenerateLakes(std::shared_ptr<WorldArea> worldArea) const;
    
    void GenerateElevation(std::shared_ptr<WorldArea> worldArea) const;
    
    void CalculateNormals(std::shared_ptr<WorldArea> worldArea) const;
};
}
