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
void WorldGenerator::GenerateWorld(Size worldAreaSize) const {
    _<World>().EnsureCreated(worldAreaSize);
    
    auto worldArea = _<World>().GetCurrentWorldArea();
    
    CreateRenderingResources(worldArea);
    GenerateGrass(worldArea);
    GenerateElevation(worldArea);
    CalculateNormals(worldArea);
}

void WorldGenerator::CreateRenderingResources(
    std::shared_ptr<WorldArea> worldArea) const {
    auto size = worldArea->GetSize();
    
    for (auto y = 0; y < size.height; y++) {
        for (auto x = 0; x < size.width; x++) {
            auto tile = worldArea->GetTile(x, y);
            if (tile) {
                tile->SetRID(_<GroundRenderer>().AllocNewTile());
            }
        }
    }
}

void WorldGenerator::GenerateGrass(std::shared_ptr<WorldArea> worldArea) const {
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

void WorldGenerator::GenerateElevation(
    std::shared_ptr<WorldArea> worldArea) const {
    auto size = worldArea->GetSize();
    auto numHills = 200;
    
    for (auto i = 0; i < numHills; i++) {
        auto xCenter = rand() % size.width;
        auto yCenter = rand() % size.height;
        auto r = 5 + rand() % 16;
        
        for (auto y = yCenter - r; y <= yCenter + r; y++) {
            for (auto x = xCenter - r; x <= xCenter +r ; x++) {
                if (false == worldArea->IsValidCoordinate(x,y))
                    continue;
                
                auto dx = x - xCenter;
                auto dy = y - yCenter;
                
                if (dx*dx + dy*dy <= r*r) {
                    auto tile = worldArea->GetTile(x,y);
                    tile->GetElevationRef() += 1.0f;
                }
            }
        }
    }
}

void WorldGenerator::CalculateNormals(
    std::shared_ptr<WorldArea> worldArea) const {
    auto tileSize = WorldViewConfiguration::k_tileSize;
    auto elevAmount = WorldViewConfiguration::k_elevAmount;
    
    for (auto y = 0; y < worldArea->GetSize().height; y++){
        for (auto x = 0; x < worldArea->GetSize().width; x++){
            
            auto tileCoord = Point2 {x, y};
            
            const auto tile = worldArea->GetTile(tileCoord.x, tileCoord.y);
            
            auto elev00 = static_cast<float>(tile->GetElevation());
            auto elev10 = elev00;
            auto elev11 = elev00;
            auto elev01 = elev00;
            
            const auto coord10 = tileCoord.Translate(1, 0);
            const auto coord11 = tileCoord.Translate(1, 1);
            const auto coord01 = tileCoord.Translate(0, 1);
            
            if (worldArea->IsValidCoordinate(coord10))
                elev10 = worldArea->GetTile(coord10)->GetElevation();
            
            if (worldArea->IsValidCoordinate(coord11))
                elev11 = worldArea->GetTile(coord11)->GetElevation();
            
            if (worldArea->IsValidCoordinate(coord01))
                elev01 = worldArea->GetTile(coord01)->GetElevation();
            
            auto x0 = tileCoord.x * tileSize;
            auto y0 = elev00 * elevAmount;
            auto z0 = tileCoord.y * tileSize;
            auto x1 = tileCoord.x * tileSize+ tileSize;
            auto y1 = elev10 * elevAmount;
            auto z1 = tileCoord.y * tileSize;
            auto x2 = tileCoord.x * tileSize+ tileSize;
            auto y2 = elev11 * elevAmount;
            auto z2 = tileCoord.y * tileSize+ tileSize;
            auto x3 = tileCoord.x * tileSize;
            auto y3 = elev01 * elevAmount;
            auto z3 = tileCoord.y * tileSize+ tileSize;
            auto p0 = Point3F {x0, y0, z0};
            auto p1 = Point3F {x1, y1, z1};
            auto p3 = Point3F {x3, y3, z3};
            
            tile->CalculateNormal(p0, p1, p3);
        }
    }
    for (auto y = 0; y < worldArea->GetSize().height; y++){
        for (auto x = 0; x < worldArea->GetSize().width; x++){
            Point2 tileCoord = {x, y};
            
            const auto tile = worldArea->GetTile(tileCoord.x, tileCoord.y);
            
            auto elev00 = static_cast<float>(tile->GetElevation());
            auto elev10 = elev00;
            auto elev11 = elev00;
            auto elev01 = elev00;
            
            const auto coord10 = tileCoord.Translate(1, 0);
            const auto coord11 = tileCoord.Translate(1, 1);
            const auto coord01 = tileCoord.Translate(0, 1);
            
            if (worldArea->IsValidCoordinate(coord10))
                elev10 = worldArea->GetTile(coord10)->GetElevation();
            
            if (worldArea->IsValidCoordinate(coord11))
                elev11 = worldArea->GetTile(coord11)->GetElevation();
            
            if (worldArea->IsValidCoordinate(coord01))
                elev01 = worldArea->GetTile(coord01)->GetElevation();
            
            auto x0 = tileCoord.x * tileSize;
            auto y0 = elev00 * elevAmount;
            auto z0 = tileCoord.y * tileSize;
            auto x1 = tileCoord.x * tileSize+ tileSize;
            auto y1 = elev10 * elevAmount;
            auto z1 = tileCoord.y * tileSize;
            auto x2 = tileCoord.x * tileSize+ tileSize;
            auto y2 = elev11 * elevAmount;
            auto z2 = tileCoord.y * tileSize+ tileSize;
            auto x3 = tileCoord.x * tileSize;
            auto y3 = elev01 * elevAmount;
            auto z3 = tileCoord.y * tileSize+ tileSize;
            
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
            
            auto redVariation = tile->GetRedVariation();
            auto greenVariation = tile->GetGreenVariation();
            auto blueVariation = tile->GetBlueVariation();
            auto redVariationEast = redVariation;
            auto greenVariationEast = greenVariation;
            auto blueVariationEast = blueVariation;
            auto redVariationSouth = redVariation;
            auto greenVariationSouth = greenVariation;
            auto blueVariationSouth = blueVariation;
            auto redVariationSouthEast = redVariation;
            auto greenVariationSouthEast = greenVariation;
            auto blueVariationSouthEast = blueVariation;
            
            if (tileCoord.x < worldArea->GetSize().width - 1){
                redVariationEast =
                    worldArea->GetTile(
                        {tileCoord.x + 1,
                         tileCoord.y})->GetRedVariation();
                
                greenVariationEast = worldArea->GetTile(
                    {tileCoord.x + 1,
                     tileCoord.y})
                                     ->GetGreenVariation();
                
                blueVariationEast =
                    worldArea->GetTile(
                        {tileCoord.x + 1,
                         tileCoord.y})->GetBlueVariation();
            }
            
            if (tileCoord.y < worldArea->GetSize().height - 1){
                redVariationSouth =
                    worldArea->GetTile(
                        {tileCoord.x,
                         tileCoord.y +
                         1})->GetRedVariation();
                
                greenVariationSouth = worldArea->GetTile(
                    {tileCoord.x,
                     tileCoord.y +
                     1})
                                      ->GetGreenVariation();
                
                blueVariationSouth=
                    worldArea->GetTile(
                        {tileCoord.x,
                         tileCoord.y +
                         1})->GetBlueVariation();
            }
            
            if (tileCoord.x < worldArea->GetSize().width - 1 &&
                tileCoord.y < worldArea->GetSize().height - 1){
                redVariationSouthEast =
                    worldArea->GetTile({tileCoord.x + 1, tileCoord.y + 1})
                    ->GetRedVariation();
                
                greenVariationSouthEast =
                    worldArea->GetTile({tileCoord.x + 1, tileCoord.y + 1})
                    ->GetGreenVariation();
                
                blueVariationSouthEast =
                    worldArea->GetTile({tileCoord.x + 1, tileCoord.y + 1})
                    ->GetBlueVariation();
            }
            
            if (tile->GetGroundType() == Hash("GroundWater")){
                redVariation = redVariationEast = redVariationSouth =
                    redVariationSouthEast = 0.0f;
                
                greenVariation = greenVariationEast =
                    greenVariationSouth =
                        greenVariationSouthEast = 0.0f;
                
                blueVariation = blueVariationEast =
                    blueVariationSouth =
                        blueVariationSouthEast = 0.0f;
            }
            
            v0.color = {
                1.0f - redVariation, 1.0f - greenVariation,
                1.0f - blueVariation, 1.0f};
            
            v1.color = {
                1.0f - redVariationEast, 1.0f - greenVariationEast,
                1.0f - blueVariationEast, 1.0f};
            
            v2.color = {
                1.0f - redVariationSouthEast,
                1.0f - greenVariationSouthEast,
                1.0f - blueVariationSouthEast, 1.0f};
            
            v3.color = {
                1.0f - redVariationSouth, 1.0f - greenVariationSouth,
                1.0f - blueVariationSouth, 1.0f};
            
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
            
            auto ridGround = tile->GetRID();
            
            _<GroundRenderer>().SetGeometryTile(
                ridGround, v0, v1, v2, v3, normal00, normal10, normal11,
                normal01);
            
            tile->SetRID(ridGround);
        }
    }
}
}
