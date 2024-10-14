#pragma once

namespace JoD {
class GroundSurfacePainter {
  public:
    void Initialize();
    
    void Paint() const;
    
  private:
    std::map<int, std::map<int, RID>> m_ridsTileLayers;
};
}
