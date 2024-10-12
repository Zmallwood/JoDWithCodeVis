/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

namespace JoD {
class GroundSurfacePainter {
  public:
    void Initialize();
    
    void Paint();
    
  private:
    std::map<int, std::map<int, RID>> m_ridsTileLayers;
};
}
