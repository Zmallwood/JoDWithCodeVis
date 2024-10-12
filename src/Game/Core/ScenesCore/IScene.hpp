#pragma once

namespace JoD {
class IScene {
  public:
    void Update();
    
    void Render();
    
  protected:
    virtual void UpdateDerived() {}
    
    virtual void RenderDerived() {}
};
}
