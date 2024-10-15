#include "FPSCounter.hpp"
#include "game/core/Engine.hpp"

namespace JoD {
FPSCounter::FPSCounter() {
    m_ridFPSText = _<Engine>().AllocateNewString();
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

void FPSCounter::Render() const {
    _<Engine>().DrawString(
        m_ridFPSText,
        "FPS: " + std::to_string(m_fps), {0.95f, 0.03f});
}
}
