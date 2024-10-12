/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

namespace JoD {
class GUIComponent {
  public:
    void Update();
    
    void Render();
    
    virtual void UpdateDerived() {}
    
    virtual void RenderDerived() {}
    
    void AddChildComponent(std::shared_ptr<GUIComponent> newComponent);
    
  private:
    std::vector<std::shared_ptr<GUIComponent>> m_childComponents;
};
}
