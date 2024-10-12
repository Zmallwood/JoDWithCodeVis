/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "GroundSurfacePainter.hpp"
#include "Theme0/Scenes/MainScene/Modules/WorldViewModule/WorldView.hpp"
#include "Game/Core/WorldStructure/Tile.hpp"
#include "Game/Core/Graphics/Rendering/GroundRendering/GroundRenderer.hpp"

namespace JoD {
void GroundSurfacePainter::Initialize() {
    auto worldAreaSize = _<WorldView>().GetWorldAreaSize();
    
    for (auto y = 0; y < worldAreaSize.height; y++)
        for (auto x = 0; x < worldAreaSize.width; x++)
            m_ridsTileLayers[x][y] = _<WorldView>().NewTile();
}

void GroundSurfacePainter::Paint() {
    auto tile = WorldView::current_tile_;
    auto tile_coord = WorldView::current_tile_coordinate_;
    auto v0 = WorldView::current_vertex_tile_.v0;
    auto v1 = WorldView::current_vertex_tile_.v1;
    auto v2 = WorldView::current_vertex_tile_.v2;
    auto v3 = WorldView::current_vertex_tile_.v3;
    auto normal00 = WorldView::current_vertex_tile_.v0.normal;
    auto normal10 = WorldView::current_vertex_tile_.v1.normal;
    auto normal11 = WorldView::current_vertex_tile_.v2.normal;
    auto normal01 = WorldView::current_vertex_tile_.v3.normal;
    auto ground_type = tile->GetGroundType();
    auto tile_variation = (tile_coord.x * tile_coord.y) % 3;
    if (ground_type == Hash("GroundWater")) {
        auto water_anim_index =
            ((SDL_GetTicks() * 2 + tile_coord.x * tile_coord.y * 6) % 2700) /
            900;
        if (water_anim_index > 0)
            ground_type = Hash(
                "GroundWater_" +
                std::to_string(water_anim_index));
        else
            ground_type = Hash("GroundWater");
    }
    else if (ground_type == Hash("GroundRiver")) {
        auto river_anim_index =
            ((SDL_GetTicks() * 3 + tile_coord.x * tile_coord.y * 6) % 2700) /
            900;
        if (river_anim_index > 0)
            ground_type = Hash(
                "GroundRiver_" +
                std::to_string(river_anim_index));
        else
            ground_type = Hash("GroundRiver");
    }
    else if (ground_type == Hash("GroundGrass")) {
        ground_type = Hash("GroundGrass_" + std::to_string(tile_variation));
    }
    else if (ground_type == Hash("GroundRock")) {
        ground_type = Hash("GroundRock_" + std::to_string(tile_variation));
    }
    ground_type = Hash("GroundGrass");
    _<GroundRenderer>().DrawTile(ground_type, tile->GetRID());
//    auto ground_layer_type = tile->GetGroundLayerType();
//    if (ground_layer_type) {
//        v0.position.y += 0.03f;
//        v1.position.y += 0.03f;
//        v2.position.y += 0.03f;
//        v3.position.y += 0.03f;
//        _<GroundRenderer>().UpdateDrawTile(
//            ground_layer_type,
//            p->rendids_tile_layers_[tile_coord.x][tile_coord.y], v0, v1, v2,
//            v3, normal00, normal10, normal11, normal01);
//    }
//    auto hovered_tile = TileHovering::Get()->hovered_tile_;
//    if (hovered_tile.x == tile_coord.x && hovered_tile.y == tile_coord.y) {
//        v0.position.y += 0.03f;
//        v1.position.y += 0.03f;
//        v2.position.y += 0.03f;
//        v3.position.y += 0.03f;
//        RendererTiles::Get()->UpdateDrawTile(
//            Hash("TileHovered"),
//            p->rendids_tile_layers_[tile_coord.x][tile_coord.y], v0, v1,
//            v2, v3, normal00, normal10, normal11, normal01);
//    }
//    auto mob = tile->GetMob().get();
//    if (MobTargeting::Get()->GetTargetedMob() == mob && nullptr != mob) {
//        v0.position.y += 0.03f;
//        v1.position.y += 0.03f;
//        v2.position.y += 0.03f;
//        v3.position.y += 0.03f;
//        RendererTiles::Get()->UpdateDrawTile(
//            Hash("TileTargetedMob"),
//            p->rendids_tile_layers_[tile_coord.x][tile_coord.y], v0,
//            v1, v2, v3, normal00, normal10, normal11, normal01);
//    }
}
}
