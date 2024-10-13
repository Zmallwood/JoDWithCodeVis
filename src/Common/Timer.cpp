/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "Timer.hpp"
#include "Common/Aliases.hpp"

namespace JoD {
Timer::Timer(float& tickSpeed)
    : m_tickSpeed(tickSpeed) {}

bool Timer::HasTick() {
    auto now = GetTicks();
    if (now > m_ticksLastUpdate + 100/m_tickSpeed) {
        m_ticksLastUpdate = now;
        return true;
    }
    
    return false;
}
}
