#pragma once

namespace JoD {
class WorldArea;

class World {
  public:
    void EnsureCreated(Size worldAreaSize);
    
    auto GetCurrentWorldArea() const {
        return m_currentWorldArea;
    }
    
  private:
    std::shared_ptr<WorldArea> m_currentWorldArea;
};
}
