/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "FPSCounter.hpp"
#include "Game/Core/Engine.hpp"

namespace JoD {
FPSCounter::FPSCounter() {
    m_ridFPSText = _<Engine>().AllocNewString();
}

void FPSCounter::Update() {
    auto now = GetTicks();
    if (now > m_ticksLastUpdate + 1000) {
        m_fps = m_framesCount;
        m_framesCount = 0;
        m_ticksLastUpdate = now;
    }
    m_framesCount++;
}

void FPSCounter::Render() {
    _<Engine>().DrawString(
        m_ridFPSText,
        "FPS: " + std::to_string(m_fps), {0.95f, 0.03f});
}
}
