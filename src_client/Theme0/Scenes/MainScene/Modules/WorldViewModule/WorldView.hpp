/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

#include "Theme0/Scenes/MainScene/MainScene.hpp"

namespace JoD {
class Tile;
class WorldArea;

class WorldView {
  public:
    void Initialize() const;
    
    void Update() const;
    
    void Render();
    
    Size GetWorldAreaSize() const;
    
    RID AllocateNewTile() const;
    
  private:
    void DoRenderLoop(std::function<void()> action);
    
  public:
    inline static int s_currentX {-1};
    inline static int s_currentY {-1};
    inline static WorldArea* s_currentWorldArea {nullptr};
    inline static Point2 s_currentTileCoordinate {-1, -1};
    inline static Tile *s_currentTile {nullptr};
    inline static VertexTile s_currentVertexTile;
    inline static Point2 s_currentCoordinate10;
    inline static Point2 s_currentCoordinate11;
    inline static Point2 s_currentCoordinate01;
    inline static int s_currentDistanceSquared {0};
    inline static float s_currentTileAvgElev {0.0f};
    inline static float s_currentElev00 {0.0f};
    inline static float s_currentElev10 {0.0f};
    inline static float s_currentElev11 {0.0f};
    inline static float s_currentElev01 {0.0f};
    inline static float s_playerTileAvgElev {0.0f};
    inline static float s_playerElev00 {0.0f};
    inline static float s_playerElev10 {0.0f};
    inline static float s_playerElev11 {0.0f};
    inline static float s_playerElev01 {0.0f};
    //inline static std::map<int, ModelRenderParameters> s_data1;
    //inline static std::map<int, ModelRenderParameters> s_data2;
};
}
