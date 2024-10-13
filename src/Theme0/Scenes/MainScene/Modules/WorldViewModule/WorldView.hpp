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
    void Initialize();
    
    void Update();
    
    void Render();
    
    Size GetWorldAreaSize();
    
    RID AllocNewTile();
    
  private:
    void DoRenderLoop(std::function<void()> action);
    
  public:
    inline static int current_x_ = -1;
    inline static int current_y_ = -1;
    inline static WorldArea* current_map_area_ = nullptr;
    inline static Point2 current_tile_coordinate_ = {-1, -1};
    inline static Tile *current_tile_ = nullptr;
    inline static VertexTile current_vertex_tile_;
    inline static Point2 current_coord10_;
    inline static Point2 current_coord11_;
    inline static Point2 current_coord01_;
    inline static bool current_this_tile_claimed_by_player_ = false;
    inline static bool current_east_tile_claimed_by_player_ = false;
    inline static bool current_south_tile_claimed_by_player_ = false;
    inline static int current_distance_squared_ = 0;
    inline static float current_tile_avg_elev_ = 0.0f;
    inline static float current_elev00_ = 0.0f;
    inline static float current_elev10_ = 0.0f;
    inline static float current_elev11_ = 0.0f;
    inline static float current_elev01_ = 0.0f;
    inline static float player_tile_avg_elev_ = 0.0f;
    inline static float player_elev00_ = 0.0f;
    inline static float player_elev10_ = 0.0f;
    inline static float player_elev11_ = 0.0f;
    inline static float player_elev01_ = 0.0f;
    //inline static std::map<int, ModelRenderParameters> data1_;
    //inline static std::map<int, ModelRenderParameters> data2_;
};
}
