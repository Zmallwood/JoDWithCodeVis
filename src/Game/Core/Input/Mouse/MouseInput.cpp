/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "MouseInput.hpp"
#include "MouseButton.hpp"

namespace JoD {
MouseInput::MouseInput()
    : m_leftButton(std::make_shared<MouseButton>()),
    m_rightButton(std::make_shared<MouseButton>()) {}

void MouseInput::RegisterButtonPressed(Uint8 button) {
    switch (button) {
    case SDL_BUTTON_LEFT:
        m_leftButton->RegisterPressed();
        break;
    case SDL_BUTTON_RIGHT:
        m_rightButton->RegisterPressed();
        break;
    }
}

void MouseInput::RegisterButtonReleased(Uint8 button) {
    switch (button) {
    case SDL_BUTTON_LEFT:
        m_leftButton->RegisterReleased();
        break;
    case SDL_BUTTON_RIGHT:
        m_rightButton->RegisterReleased();
        break;
    }
}

bool MouseInput::AnyButtonIsPressed() const {
    return m_leftButton->GetIsPressed() || m_rightButton->GetIsPressed();
}
}
