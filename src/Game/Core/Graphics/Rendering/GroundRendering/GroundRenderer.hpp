/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

#include "Game/Core/Graphics/Rendering/RenderingCore/RendererBase.hpp"

namespace JoD {
class GroundRenderer : public RendererBase {
  public:
    GroundRenderer();
    RID NewTile();
    void SetGeometryTile(
        RID vaoId, Vertex3F &v0, Vertex3F &v1, Vertex3F &v2, Vertex3F &v3,
        Point3F &normal00,
        Point3F &normal10, Point3F &normal11, Point3F &normal01
        ) const;
    void DrawTile(int imageNameHash, RID vaoId,
                  bool depthTestOff = false) const;
    void UpdateDrawTile(
        int imageNameHash, RID vaoId, Vertex3F &v0, Vertex3F &v1, Vertex3F &v2,
        Vertex3F &v3,
        Point3F &normal00, Point3F &normal10, Point3F &normal11,
        Point3F &normal01,
        bool depthTestOff = false
        ) const;
    void StartBatchDrawing();
    void StopBatchDrawing();
    void Cleanup();
    
  private:
    void DrawImagePolygon(int imageNameHash, RID vaoId, int vertexCount,
                          bool depthTestOffint = false) const;
    RID NewImagePolygon(int numVertices);
    void SetGeometryImagePolygon(RID vaoId,
                                 std::vector<Vertex3F> &vertices) const;
    
    const int k_LocationPosition {0};
    const int k_LocationColor {1};
    const int k_LocationUv {2};
    const int k_LocationNormal {3};
    int m_locationProjection {-1};
    int m_locationView {-1};
    int m_locationModel {-1};
    int m_locationAlpha {-1};
    int m_locationViewPos {-1};
    int m_locationFogColor {-1};
    bool m_isBatchDrawing {false};
};
}
