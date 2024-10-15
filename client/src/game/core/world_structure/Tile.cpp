/*
 * Copyright 2024 Andreas Åkerberg.
 */

#include "Tile.hpp"

namespace JoD {
void Tile::SetGroundType(std::string_view groundTypeName) {
    m_groundType = Hash(groundTypeName);
}

void Tile::CalculateNormal(Point3F v0, Point3F v1, Point3F v2) {
    auto point0 = glm::vec3(v0.x, v0.y, v0.z);
    auto point1 = glm::vec3(v1.x, v1.y, v1.z);
    auto Point2 = glm::vec3(v2.x, v2.y, v2.z);
    auto vector0 = point1 - point0;
    auto vector1 = Point2 - point0;
    auto vector2 = glm::cross(vector0, vector1);
    auto normalGl = glm::normalize(vector2);
    m_normal = {-normalGl.x, -normalGl.y, -normalGl.z};
}

void Tile::SetVertex0(Vertex3F vertex) {
    m_geometry[0] = vertex;
}

void Tile::SetVertex1(Vertex3F vertex) {
    m_geometry[1] = vertex;
}

void Tile::SetVertex2(Vertex3F vertex) {
    m_geometry[2] = vertex;
}

void Tile::SetVertex3(Vertex3F vertex) {
    m_geometry[3] = vertex;
}
}
