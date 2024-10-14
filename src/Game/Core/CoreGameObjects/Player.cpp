/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "Player.hpp"
#include \
    "Theme0/Scenes/MainScene/Modules/WorldViewModule/WorldViewConfiguration.hpp"

namespace JoD {
void Player::MoveNorth() {
    m_position.y--;
}

void Player::MoveEast() {
    m_position.x++;
}

void Player::MoveSouth() {
    m_position.y++;
}

void Player::MoveWest() {
    m_position.x--;
}

Point3F Player::GetPosition3D() const {
    auto position3D= Point3F {m_position.x * WorldViewConfiguration::k_tileSize,
                              0.0f,
                              m_position.y*WorldViewConfiguration::k_tileSize};
    return position3D;
}
}
