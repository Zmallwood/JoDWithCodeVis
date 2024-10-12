/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

namespace JoD {
class KeyboardInput {
  public:
    void RegisterKeyPress(SDL_Keycode key);
    
    void RegisterKeyRelease(SDL_Keycode key);
    
    void AppendTextInput(std::string_view newText);
    
    bool AnyKeyIsPressed() const;
    
  private:
    std::set<SDL_Keycode> m_pressedKeys;
    std::string m_textInput;
};
}
