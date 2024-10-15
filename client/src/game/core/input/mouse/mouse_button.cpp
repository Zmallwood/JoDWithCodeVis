/*
 * Copyright 2024 Andreas Åkerberg.
 */
#include "MouseButton.hpp"

namespace JoD {
void MouseButton::Reset() {
  m_isPressed = false;
  m_hasBeenFired = false;
  m_hasBeenReleased = false;
}

void MouseButton::RegisterPressed() {
  m_isPressed = true;
  m_hasBeenFired = true;
}

void MouseButton::RegisterReleased() {
  m_isPressed = false;
  m_hasBeenReleased = true;
}

bool MouseButton::HasBeenFiredPickResult() {
  auto result = m_hasBeenFired;
  m_hasBeenFired = false;
  return result;
}

bool MouseButton::HasBeenReleasedPickResult() {
  auto result= m_hasBeenReleased;
  m_hasBeenReleased = false;
  return result;
}
}
