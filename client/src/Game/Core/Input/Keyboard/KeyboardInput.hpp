#pragma once

namespace JoD {
class KeyboardInput {
  public:
    void Reset();
    
    void RegisterKeyPress(SDL_Keycode key);
    
    void RegisterKeyRelease(SDL_Keycode key);
    
    void AppendTextInput(std::string_view newText);
    
    bool AnyKeyIsPressed() const;
    
    bool KeyIsPressed(SDL_Keycode key) const;
    
  private:
    std::set<SDL_Keycode> m_pressedKeys;
    std::string m_textInput;
};
}
