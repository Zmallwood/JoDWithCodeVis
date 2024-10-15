/*
 * Copyright 2024 Andreas Åkerberg.
 */
#include "timer.hpp"
#include "common/aliases.hpp"

namespace JoD {
Timer::Timer(float& tickSpeed)
  : m_tickSpeed(tickSpeed) {
  if (tickSpeed <= 0.0f)
    throw std::invalid_argument(
            CodeLocation() +
            "tickSpeed must be a value greated than 0.0f.");
}

bool Timer::HasTick() {
  auto now = GetTicks();
  if (now > m_ticksLastUpdate + 100/m_tickSpeed){
    m_ticksLastUpdate = now;
    return true;
  }
  return false;
}
}
