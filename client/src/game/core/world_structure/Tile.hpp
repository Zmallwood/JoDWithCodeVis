/*
 * Copyright 2024 Andreas Åkerberg.
 */

#pragma once

namespace JoD {
class Tile {
  public:
    void SetGroundType(std::string_view groundTypeName);
    
    void CalculateNormal(Point3F v0, Point3F v1, Point3F v2);
    
    auto GetGroundType() const {
        return m_groundType;
    }
    
    auto GetElevation() const {
        return m_elevation;
    }
    
    auto &GetElevationRef() {
        return m_elevation;
    }
    
    auto GetNormal() const {
        return m_normal;
    }
    
    auto GetRID() const {
        return m_rid;
    }
    
    void SetRID(RID value) {
        m_rid = value;
    }
    
    auto GetRedVariation() const {
        return m_redVariation;
    }
    
    void SetRedVariation(float value) {
        m_redVariation = value;
    }
    
    auto GetGreenVariation() const {
        return m_greenVariation;
    }
    
    void SetGreenVariation(float value) {
        m_greenVariation = value;
    }
    
    auto GetBlueVariation() const {
        return m_blueVariation;
    }
    
    void SetBlueVariation(float value) {
        m_blueVariation = value;
    }
    
    void SetVertex0(Vertex3F vertex);
    
    void SetVertex1(Vertex3F vertex);
    
    void SetVertex2(Vertex3F vertex);
    
    void SetVertex3(Vertex3F vertex);
    
  private:
    int m_groundType {0};
    float m_elevation {0.0f};
    Point3F m_normal {0.0f, 0.0f, 0.0f};
    RID m_rid {0};
    float m_redVariation {0.0f};
    float m_greenVariation {0.0f};
    float m_blueVariation {0.0f};
    std::array<Vertex3F, 4> m_geometry;
};
}
