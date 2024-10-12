/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

namespace JoD {
class GUI;

class IScene {
  public:
    IScene();
    
    void OnEnter();
    
    void Update();
    
    void Render();
    
  protected:
    virtual void OnEnterDerived() {}
    
    virtual void UpdateDerived() {}
    
    virtual void RenderDerived() {}
    
    auto GetGUI() {
        return m_gui;
    }
    
  private:
    std::shared_ptr<GUI> m_gui;
};
}
