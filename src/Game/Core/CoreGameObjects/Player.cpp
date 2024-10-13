/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "Player.hpp"

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
    auto position3D= Point3F {m_position.x, 0.0f, m_position.y};
    return position3D;
}
}
