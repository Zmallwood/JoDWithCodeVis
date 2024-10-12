/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "Tile.hpp"

namespace JoD {
void Tile::SetGround(std::string_view groundName) {
    m_ground = Hash(groundName);
}
}
