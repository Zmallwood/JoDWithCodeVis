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
            m_ridsTileLayers[x][y] = _<WorldView>().AllocNewTile();
}

void GroundSurfacePainter::Paint() {
    auto tile = WorldView::s_currentTile;
    auto tileCoord= WorldView::s_currentTileCoordinate;
    
    auto v0 = WorldView::s_currentVertexTile.v0;
    auto v1 = WorldView::s_currentVertexTile.v1;
    auto v2 = WorldView::s_currentVertexTile.v2;
    auto v3 = WorldView::s_currentVertexTile.v3;
    
    auto normal00 = WorldView::s_currentVertexTile.v0.normal;
    auto normal10 = WorldView::s_currentVertexTile.v1.normal;
    auto normal11 = WorldView::s_currentVertexTile.v2.normal;
    auto normal01 = WorldView::s_currentVertexTile.v3.normal;
    
    auto groundType= tile->GetGroundType();
    auto tile_variation = (tileCoord.x * tileCoord.y) % 3;
    
    if (groundType == Hash("GroundWater")) {
        auto waterAnimIndex =
            ((SDL_GetTicks() * 2 + tileCoord.x * tileCoord.y * 6) % 2700) /
            900;
        if (waterAnimIndex > 0)
            groundType = Hash(
                "GroundWater_" +
                std::to_string(waterAnimIndex));
        else
            groundType = Hash("GroundWater");
    }
    else if (groundType == Hash("GroundRiver")) {
        auto riverAnimIndex =
            ((SDL_GetTicks() * 3 + tileCoord.x * tileCoord.y * 6) % 2700) /
            900;
        if (riverAnimIndex> 0)
            groundType = Hash(
                "GroundRiver_" +
                std::to_string(riverAnimIndex));
        else
            groundType = Hash("GroundRiver");
    }
    else if (groundType == Hash("GroundGrass")) {
        groundType = Hash("GroundGrass_" + std::to_string(tile_variation));
    }
    else if (groundType == Hash("GroundRock")) {
        groundType = Hash("GroundRock_" + std::to_string(tile_variation));
    }
    
    groundType = Hash("GroundGrass");
    
    _<GroundRenderer>().DrawTile(groundType, tile->GetRID());
    
//    auto groundLayerType = tile->GetGroundLayerType();
//
//    if (groundLayerType) {
//        v0.position.y += 0.03f;
//        v1.position.y += 0.03f;
//        v2.position.y += 0.03f;
//        v3.position.y += 0.03f;
//        _<GroundRenderer>().UpdateDrawTile(
//            groundLayerType,
//            p->rendids_tile_layers_[tile_coord.x][tile_coord.y], v0, v1, v2,
//            v3, normal00, normal10, normal11, normal01);
//    }
//
//    auto hoveredType = TileHovering::Get()->hovered_tile_;
//
//    if (hoveredType.x == tileCoord.x && hoveredType.y == tileCoord.y) {
//        v0.position.y += 0.03f;
//        v1.position.y += 0.03f;
//        v2.position.y += 0.03f;
//        v3.position.y += 0.03f;
//        RendererTiles::Get()->UpdateDrawTile(
//            Hash("TileHovered"),
//            m_ridsTileLayers[tileCoord.x][tileCoord.y], v0, v1,
//            v2, v3, normal00, normal10, normal11, normal01);
//    }
//
//    auto mob = tile->GetMob().get();
//
//    if (MobTargeting::Get()->GetTargetedMob() == mob && nullptr != mob) {
//        v0.position.y += 0.03f;
//        v1.position.y += 0.03f;
//        v2.position.y += 0.03f;
//        v3.position.y += 0.03f;
//        RendererTiles::Get()->UpdateDrawTile(
//            Hash("TileTargetedMob"),
//            m_ridsTileLayers[tileCoord.x][tileCoord.y], v0,
//            v1, v2, v3, normal00, normal10, normal11, normal01);
//    }
}
}
