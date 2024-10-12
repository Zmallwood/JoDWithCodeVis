/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "WorldGenerator.hpp"
#include "Game/Core/WorldStructure/World.hpp"
#include "Game/Core/WorldStructure/WorldArea.hpp"
#include "Game/Core/WorldStructure/Tile.hpp"
#include "Game/Core/Graphics/Rendering/GroundRendering/GroundRenderer.hpp"
#include \
    "Theme0/Scenes/MainScene/Modules/WorldViewModule/WorldViewConfiguration.hpp"

namespace JoD {
void WorldGenerator::GenerateWorld(Size worldAreaSize) {
    _<World>().EnsureCreated(worldAreaSize);
    auto worldArea = _<World>().GetCurrentWorldArea();
    CreateRenderingResources(worldArea);
    GenerateGrass(worldArea);
    CalculateNormals(worldArea);
}

void WorldGenerator::CreateRenderingResources(
    std::shared_ptr<WorldArea> worldArea) {
    auto size = worldArea->GetSize();
    
    for (auto y = 0; y < size.height; y++) {
        for (auto x = 0; x < size.width; x++) {
            auto tile = worldArea->GetTile(x, y);
            if (tile) {
                tile->SetRID(_<GroundRenderer>().NewTile());
            }
        }
    }
}


void WorldGenerator::GenerateGrass(std::shared_ptr<WorldArea> worldArea) {
    auto size = worldArea->GetSize();
    
    for (auto y = 0; y < size.height; y++) {
        for (auto x = 0; x < size.width; x++) {
            auto tile = worldArea->GetTile(x, y);
            if (tile) {
                tile->SetGroundType("GroundGrass");
            }
        }
    }
}

void WorldGenerator::CalculateNormals(std::shared_ptr<WorldArea> worldArea) {
    auto tileSize = WorldViewConfiguration::k_tileSize;
    auto elevAmount = WorldViewConfiguration::k_elevAmount;
    for (auto y = 0; y < worldArea->GetSize().height; y++){
        for (auto x = 0; x < worldArea->GetSize().width; x++){
            auto tile_coord = Point2{x, y};
            const auto tile = worldArea->GetTile(tile_coord.x, tile_coord.y);
            const auto elev00 = static_cast<float>(tile->GetElevation());
            auto elev10 = elev00;
            auto elev11 = elev00;
            auto elev01 = elev00;
            const auto coord10 = tile_coord.Translate(1, 0);
            const auto coord11 = tile_coord.Translate(1, 1);
            const auto coord01 = tile_coord.Translate(0, 1);
            if (worldArea->IsValidCoordinate(coord10))
                elev10 = worldArea->GetTile(coord10)->GetElevation();
            if (worldArea->IsValidCoordinate(coord11))
                elev11 = worldArea->GetTile(coord11)->GetElevation();
            if (worldArea->IsValidCoordinate(coord01))
                elev01 = worldArea->GetTile(coord01)->GetElevation();
            auto x0 = tile_coord.x * tileSize;
            auto y0 = elev00 * elevAmount;
            auto z0 = tile_coord.y * tileSize;
            auto x1 = tile_coord.x * tileSize+ tileSize;
            auto y1 = elev10 * elevAmount;
            auto z1 = tile_coord.y * tileSize;
            auto x2 = tile_coord.x * tileSize+ tileSize;
            auto y2 = elev11 * elevAmount;
            auto z2 = tile_coord.y * tileSize+ tileSize;
            auto x3 = tile_coord.x * tileSize;
            auto y3 = elev01 * elevAmount;
            auto z3 = tile_coord.y * tileSize+ tileSize;
            auto p0 = Point3F{x0, y0, z0};
            auto p1 = Point3F{x1, y1, z1};
            auto p3 = Point3F{x3, y3, z3};
            tile->CalculateNormal(p0, p1, p3);
        }
    }
    for (auto y = 0; y < worldArea->GetSize().height; y++){
        for (auto x = 0; x < worldArea->GetSize().width; x++){
            Point2 tile_coord = {x, y};
            const auto tile = worldArea->GetTile(tile_coord.x, tile_coord.y);
            const auto elev00 = static_cast<float>(tile->GetElevation());
            auto elev10 = elev00;
            auto elev11 = elev00;
            auto elev01 = elev00;
            const auto coord10 = tile_coord.Translate(1, 0);
            const auto coord11 = tile_coord.Translate(1, 1);
            const auto coord01 = tile_coord.Translate(0, 1);
            if (worldArea->IsValidCoordinate(coord10))
                elev10 = worldArea->GetTile(coord10)->GetElevation();
            if (worldArea->IsValidCoordinate(coord11))
                elev11 = worldArea->GetTile(coord11)->GetElevation();
            if (worldArea->IsValidCoordinate(coord01))
                elev01 = worldArea->GetTile(coord01)->GetElevation();
            auto x0 = tile_coord.x * tileSize;
            auto y0 = elev00 * elevAmount;
            auto z0 = tile_coord.y * tileSize;
            auto x1 = tile_coord.x * tileSize+ tileSize;
            auto y1 = elev10 * elevAmount;
            auto z1 = tile_coord.y * tileSize;
            auto x2 = tile_coord.x * tileSize+ tileSize;
            auto y2 = elev11 * elevAmount;
            auto z2 = tile_coord.y * tileSize+ tileSize;
            auto x3 = tile_coord.x * tileSize;
            auto y3 = elev01 * elevAmount;
            auto z3 = tile_coord.y * tileSize+ tileSize;
            Vertex3F v0;
            Vertex3F v1;
            Vertex3F v2;
            Vertex3F v3;
            v0.position = {x0, y0, z0};
            v1.position = {x1, y1, z1};
            v2.position = {x2, y2, z2};
            v3.position = {x3, y3, z3};
            v0.uv = {0.0f, 0.0f};
            v1.uv = {1.0f, 0.0f};
            v2.uv = {1.0f, 1.0f};
            v3.uv = {0.0f, 1.0f};
            auto red_variation = tile->GetRedVariation();
            auto green_variation = tile->GetGreenVariation();
            auto blue_variation = tile->GetBlueVariation();
            auto red_variation_east = red_variation;
            auto green_variation_east = green_variation;
            auto blue_variation_east = blue_variation;
            auto red_variation_south = red_variation;
            auto green_variation_south = green_variation;
            auto blue_variation_south = blue_variation;
            auto red_variation_south_east = red_variation;
            auto green_variation_south_east = green_variation;
            auto blue_variation_south_east = blue_variation;
            if (tile_coord.x < worldArea->GetSize().width - 1){
                red_variation_east =
                    worldArea->GetTile(
                        {tile_coord.x + 1,
                         tile_coord.y})->GetRedVariation();
                green_variation_east = worldArea->GetTile(
                    {tile_coord.x + 1,
                     tile_coord.y})
                                       ->GetGreenVariation();
                blue_variation_east =
                    worldArea->GetTile(
                        {tile_coord.x + 1,
                         tile_coord.y})->GetBlueVariation();
            }
            if (tile_coord.y < worldArea->GetSize().height - 1){
                red_variation_south =
                    worldArea->GetTile(
                        {tile_coord.x,
                         tile_coord.y +
                         1})->GetRedVariation();
                green_variation_south = worldArea->GetTile(
                    {tile_coord.x,
                     tile_coord.y +
                     1})
                                        ->GetGreenVariation();
                blue_variation_south =
                    worldArea->GetTile(
                        {tile_coord.x,
                         tile_coord.y +
                         1})->GetBlueVariation();
            }
            if (tile_coord.x < worldArea->GetSize().width - 1 &&
                tile_coord.y < worldArea->GetSize().height - 1){
                red_variation_south_east =
                    worldArea->GetTile({tile_coord.x + 1, tile_coord.y + 1})
                    ->GetRedVariation();
                green_variation_south_east =
                    worldArea->GetTile({tile_coord.x + 1, tile_coord.y + 1})
                    ->GetGreenVariation();
                blue_variation_south_east =
                    worldArea->GetTile({tile_coord.x + 1, tile_coord.y + 1})
                    ->GetBlueVariation();
            }
            if (tile->GetGroundType() == Hash("GroundWater")){
                red_variation = red_variation_east = red_variation_south =
                    red_variation_south_east = 0.0f;
                green_variation = green_variation_east =
                    green_variation_south =
                        green_variation_south_east = 0.0f;
                blue_variation = blue_variation_east =
                    blue_variation_south =
                        blue_variation_south_east = 0.0f;
            }
            v0.color = {
                1.0f - red_variation, 1.0f - green_variation,
                1.0f - blue_variation, 1.0f};
            v1.color = {
                1.0f - red_variation_east, 1.0f - green_variation_east,
                1.0f - blue_variation_east, 1.0f};
            v2.color = {
                1.0f - red_variation_south_east,
                1.0f - green_variation_south_east,
                1.0f - blue_variation_south_east, 1.0f};
            v3.color = {
                1.0f - red_variation_south, 1.0f - green_variation_south,
                1.0f - blue_variation_south, 1.0f};
            tile->SetVertex0(v0);
            tile->SetVertex1(v1);
            tile->SetVertex2(v2);
            tile->SetVertex3(v3);
            auto normal00 = tile->GetNormal();
            auto normal10 = normal00;
            auto normal11 = normal00;
            auto normal01 = normal00;
            if (worldArea->IsValidCoordinate(coord10))
                normal10 = worldArea->GetTile(coord10)->GetNormal();
            if (worldArea->IsValidCoordinate(coord11))
                normal11 = worldArea->GetTile(coord11)->GetNormal();
            if (worldArea->IsValidCoordinate(coord01))
                normal01 = worldArea->GetTile(coord01)->GetNormal();
            GLuint rendid_ground;
//            if (false == updateExistingTiles){
//                rendid_ground = RendererTiles::Get()->NewTile();
//            }
//            else{
            rendid_ground = tile->GetRID();
//            }
            _<GroundRenderer>().SetGeometryTile(
                rendid_ground, v0, v1, v2, v3, normal00, normal10, normal11,
                normal01);
            tile->SetRID(rendid_ground);
        }
    }
}
}
