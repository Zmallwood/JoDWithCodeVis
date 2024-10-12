/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "Player.hpp"

namespace JoD {
Point3F Player::GetPosition3D() {
    auto position3D= Point3F {m_position.x, 0.0f, m_position.y};
    return position3D;
}
}
