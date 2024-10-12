#include "MouseButton.hpp"

namespace JoD {
void MouseButton::RegisterPressed() {
    m_isPressed = true;
}

void MouseButton::RegisterReleased() {
    m_isPressed = false;
}
}
