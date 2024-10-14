#include "MouseInput.hpp"
#include "MouseButton.hpp"

namespace JoD {
MouseInput::MouseInput()
    : m_leftButton(std::make_shared<MouseButton>()),
    m_rightButton(std::make_shared<MouseButton>()) {}

void MouseInput::Reset() {
    m_mouseWheelDelta = 0;
    m_motionDelta = {0, 0};
    m_leftButton->Reset();
    m_rightButton->Reset();
}

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

void MouseInput::RegisterMouseMoved(Point2 delta) {
    m_motionDelta = delta;
}

void MouseInput::RegisterMouseWheelScrolled(int delta) {
    m_mouseWheelDelta += delta;
}

bool MouseInput::AnyMouseButtonIsPressed() const {
    return m_leftButton->GetIsPressed() || m_rightButton->GetIsPressed();
}

int MouseInput::GetMouseWheelDeltaPickResult() {
    auto result = m_mouseWheelDelta;
    m_mouseWheelDelta = 0;
    return result;
}

Point2 MouseInput::GetMotionDeltaPickResult() {
    auto result = m_motionDelta;
    m_motionDelta = {0, 0};
    return result;
}
}
