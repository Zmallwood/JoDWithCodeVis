/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "KeyboardInput.hpp"

namespace JoD {
void KeyboardInput::RegisterKeyPress(SDL_Keycode key) {
    m_pressedKeys.insert(key);
}

void KeyboardInput::RegisterKeyRelease(SDL_Keycode key) {
    m_pressedKeys.erase(key);
}

void KeyboardInput::AppendTextInput(std::string_view newText) {
    m_textInput.append(newText);
}

bool KeyboardInput::AnyKeyIsPressed() const {
    return m_pressedKeys.size() > 0;
}
}
