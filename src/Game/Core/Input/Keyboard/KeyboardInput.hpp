#pragma once

namespace JoD {
class KeyboardInput {
  public:
    void RegisterKeyPress(SDL_Keycode key);
    
    void RegisterKeyRelease(SDL_Keycode key);
    
    bool AnyKeyIsPressed() const;
    
  private:
    std::set<SDL_Keycode> m_pressedKeys;
};
}
