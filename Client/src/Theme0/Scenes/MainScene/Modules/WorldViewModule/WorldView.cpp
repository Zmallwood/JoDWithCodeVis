/*
 * Copyright 2024 Andreas Åkerberg.
 */

#include "WorldView.hpp"
#include "Game/Core/Graphics/Rendering/GroundRendering/GroundRenderer.hpp"
#include "SubPainters/GroundSurfacePainter.hpp"
#include "Camera.hpp"
#include "Game/Core/CoreGameObjects/Player.hpp"
#include "Game/Core/WorldStructure/World.hpp"
#include "Game/Core/WorldStructure/WorldArea.hpp"
#include "Game/Core/WorldStructure/Tile.hpp"
#include "WorldViewConfiguration.hpp"
#include "Game/Core/Graphics/Rendering/CameraGL.hpp"

namespace JoD {
void WorldView::Initialize() const {
    _<GroundSurfacePainter>().Initialize();
}

void WorldView::Update() const {
    try {
        _<Camera>().Update();
    }
    catch (const std::runtime_error& e) {
        std::cout <<
            "Exception of \"runtime error\" type occured in WorldView::Update():\n\""
                  <<
            e.what() << "\"\n";
        throw;
    }
    catch (const std::invalid_argument& e) {
        std::cout <<
            "Exception of \"invalid argument\" type occured in WorldView::Update():\n\""
                  <<
            e.what() << "\"\n";
        throw;
    }
    catch (const std::exception& e) {
        std::cout <<
            "Exception of unhandled type occured in WorldView::Update():\n\"" <<
            e.what() <<
            "\"\n";
        throw;
    }
}

void WorldView::Render() {
    try {
        _<GroundRenderer>().StartBatchDrawing();
        DoRenderLoop(
            [] {
                _<GroundSurfacePainter>().Paint();
            });
        _<GroundRenderer>().StopBatchDrawing();
    }
    catch (const std::runtime_error& e) {
        std::cout <<
            "Exception of \"runtime error\" type occured in WorldView::Render():\n\""
                  <<
            e.what() << "\"\n";
        throw;
    }
    catch (const std::invalid_argument& e) {
        std::cout <<
            "Exception of \"invalid argument\" type occured in WorldView::Render():\n\""
                  <<
            e.what() << "\"\n";
        throw;
    }
    catch (const std::exception& e) {
        std::cout <<
            "Exception of unhandled type occured in WorldView::Render():\n\"" <<
            e.what() <<
            "\"\n";
        throw;
    }
}

void WorldView::DoRenderLoop(std::function<void()> action) {
    auto playerWorldAreaPosition = _<Player>().GetMajorCoordinate();
    auto playerPosition= _<Player>().GetPosition();
    auto playerTileCoord= playerPosition.ToIntPoint();
    auto worldArea =
        _<World>().GetCurrentWorldArea();
    s_currentWorldArea = worldArea.get();
    auto &camera = _<Camera>();
    auto elev_amount = WorldViewConfiguration::k_elevAmount;
    auto canvas_size = GetCanvasSize();
    auto perspective_matrix = _<CameraGL>().GetPerspectiveMatrix();
    auto view_port =
        glm::vec4(
            0.0f, canvas_size.height / 2, canvas_size.width,
            canvas_size.height);
    float camera_offset_amount = WorldViewConfiguration::k_tileSize* 10.0f;
    auto angle = std::atan2(
        camera.GetCameraPositionRef().z - playerTileCoord.y *
        WorldViewConfiguration::k_tileSize,
        camera.GetCameraPositionRef().x - playerTileCoord.x *
        WorldViewConfiguration::k_tileSize);
    auto extra_distance = std::max(
        (float)std::sin((camera.GetVerticalAngle()) * M_PI / 180.0f) *
        camera_offset_amount,
        0.0f);
    float p_camera_dx = std::cos(angle) *
                        ((camera_offset_amount + extra_distance) *
                         camera.GetCameraDistance() / 30.0f);
    float p_camera_dz = std::sin(angle) *
                        ((camera_offset_amount + extra_distance) *
                         camera.GetCameraDistance() / 30.0f);
    Point3F usedPos = Point3F{
        playerTileCoord.x * WorldViewConfiguration::k_tileSize + p_camera_dx,
        0.0f,
        playerTileCoord.y * WorldViewConfiguration::k_tileSize + p_camera_dz};
    float angle_radians = -(camera.GetHorizontalAngle()) *
                          static_cast<float>(M_PI) / 180.0f;
    auto up = glm::vec3(0.0f, 1.0f, 0.0f);
    auto model_matrix = glm::rotate(glm::mat4(1.0), angle_radians, up);
    auto render_radius =
        static_cast<int>(WorldViewConfiguration::k_maxRenderRadius* 0.7f);
    for (auto y = -render_radius; y < render_radius; y++){
        for (auto x = -render_radius; x < render_radius; x++){
            s_currentX = x;
            s_currentY = y;
            Point2 tile_coord = {playerTileCoord.x + x,
                                 playerTileCoord.y + y};
            s_currentTileCoordinate = tile_coord;
            if (!worldArea->IsValidCoordinate(tile_coord.x, tile_coord.y))
                continue;
            auto distance_squared = x * x + y * y;
            if (distance_squared > render_radius * render_radius)
                continue;
            s_currentDistanceSquared = distance_squared;
            auto tile = worldArea->GetTile(tile_coord.x, tile_coord.y);
            s_currentTile = tile.get();
            auto elev00 = static_cast<float>(tile->GetElevation());
            auto elev10 = elev00;
            auto elev11 = elev00;
            auto elev01 = elev00;
            auto coord10 = tile_coord.Translate(1, 0);
            auto coord11 = tile_coord.Translate(1, 1);
            auto coord01 = tile_coord.Translate(0, 1);
            s_currentCoordinate10 = coord10;
            s_currentCoordinate11 = coord11;
            s_currentCoordinate01 = coord01;
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
            if (worldArea->IsValidCoordinate(coord10))
                elev10 = worldArea->GetTile(coord10)->GetElevation();
            if (worldArea->IsValidCoordinate(coord11))
                elev11 = worldArea->GetTile(coord11)->GetElevation();
            if (worldArea->IsValidCoordinate(coord01))
                elev01 = worldArea->GetTile(coord01)->GetElevation();
            s_currentElev00 = elev00;
            s_currentElev10 = elev10;
            s_currentElev11 = elev11;
            s_currentElev01 = elev01;
            auto x0 = tile_coord.x * WorldViewConfiguration::k_tileSize;
            auto y0 = elev00 * elev_amount;
            auto z0 = tile_coord.y * WorldViewConfiguration::k_tileSize;
            auto x1 = tile_coord.x * WorldViewConfiguration::k_tileSize +
                      WorldViewConfiguration::k_tileSize;
            auto y1 = elev10 * elev_amount;
            auto z1 = tile_coord.y * WorldViewConfiguration::k_tileSize;
            auto x2 = tile_coord.x * WorldViewConfiguration::k_tileSize +
                      WorldViewConfiguration::k_tileSize;
            auto y2 = elev11 * elev_amount;
            auto z2 = tile_coord.y * WorldViewConfiguration::k_tileSize +
                      WorldViewConfiguration::k_tileSize;
            auto x3 = tile_coord.x * WorldViewConfiguration::k_tileSize;
            auto y3 = elev01 * elev_amount;
            auto z3 = tile_coord.y * WorldViewConfiguration::k_tileSize +
                      WorldViewConfiguration::k_tileSize;
            auto tile_avg_elev = (elev00 + elev10 + elev01 + elev11) / 4.0f;
            s_currentTileAvgElev = tile_avg_elev;
            if (tile_coord.x == playerTileCoord.x &&
                tile_coord.y == playerTileCoord.y){
                s_playerElev00 = elev00;
                s_playerElev10 = elev10;
                s_playerElev11 = elev11;
                s_playerElev01 = elev01;
                s_playerTileAvgElev = tile_avg_elev;
            }
            glm::vec3 cRel =
                glm::vec3{(x0 + x2) / 2.0f - usedPos.x, 0,
                          (z0 + z2) / 2.0f - usedPos.z};
            auto screen_coord = glm::project(
                cRel, model_matrix,
                perspective_matrix, view_port);
            if (_<Camera>().GetCameraDistance() > 10.0f)
                if (screen_coord.x <= -0.4f * canvas_size.width ||
                    screen_coord.x >= canvas_size.width * 1.4f)
                    continue;
            VertexTile vertex_tile;
            vertex_tile.v0.position = {x0, y0, z0};
            vertex_tile.v1.position = {x1, y1, z1};
            vertex_tile.v2.position = {x2, y2, z2};
            vertex_tile.v3.position = {x3, y3, z3};
            vertex_tile.v0.normal = normal00;
            vertex_tile.v1.normal = normal10;
            vertex_tile.v2.normal = normal11;
            vertex_tile.v3.normal = normal01;
            s_currentVertexTile = vertex_tile;
//            bool do_draw_objects = true;
//
//            if (do_draw_objects){
//                for (auto &object_entry : tile->GetObjects().list_){
//                    auto object_type = object_entry->GetObjectType();
//                    auto object_scaling = object_entry->GetModelScaling();
//                    auto object_rotation = object_entry->GetModelRotation();
//                    auto animation_value =
//                        (tile_coord.x * tile_coord.y * 10 + SDL_GetTicks() * 2);
//
//                    auto red_variation = object_entry->GetRedVariation();
//                    auto green_variation = object_entry->GetGreenVariation();
//                    auto blue_variation = object_entry->GetBlueVariation();
//
//                    bool shadow_already_drawn = false;
//
//                    if (object_type){
//                        std::map<int, ModelRenderParameters> *data = nullptr;
//
//                        if ((tile_coord.x + tile_coord.y) % 2 == 0)
//                            data = &data1_;
//                        else
//                            data = &data2_;
//
//                        if (data->count(Hash("Shadow")) == 0)
//                            data->insert(
//                                {Hash("Shadow"),
//                                 ModelRenderParameters()});
//
//                        if (!shadow_already_drawn){
//                            if (distance_squared < 600){
//                                if (object_type != Hash("ObjectTallGrass6") &&
//                                    (false ==
//                                     ObjectBehaviourList::Get()->
//                                     HasBehaviourData(
//                                         object_type) ||
//                                     ObjectBehaviourList::Get()->GetFlags(
//                                         object_type) &
//                                     (int)ObjectBehaviourFlags::NoShadow == 0)){
//                                    data->at(Hash("Shadow"))
//                                    .positions.push_back(
//                                        {x0 + kTileSize / 2,
//                                         tile_avg_elev * elev_amount + 0.05f *
//                                         kTileSize,
//                                         z0 + kTileSize / 2});
//                                    data->at(
//                                        Hash(
//                                            "Shadow")).rotations.push_back(
//                                        0.0f);
//                                    data->at(Hash("Shadow")).scalings.push_back(
//                                        1.5f);
//                                    data->at(
//                                        Hash(
//                                            "Shadow")).brightnesses.
//                                    push_back(1.0f);
//                                    data->at(Hash("Shadow"))
//                                    .colorMods.push_back({1.0f, 1.0f, 1.0f});
//                                    shadow_already_drawn = true;
//                                }
//                            }
//                        }
//
//                        if (data->count(object_type) == 0)
//                            data->insert(
//                                {object_type,
//                                 ModelRenderParameters()});
//
//                        auto animation_value =
//                            (tile_coord.x * tile_coord.y * 10 + SDL_GetTicks() *
//                             2);
//                        data->at(object_type)
//                        .positions.push_back(
//                            {x0 + kTileSize / 2, tile_avg_elev * elev_amount,
//                             z0 + kTileSize / 2});
//                        data->at(object_type).rotations.push_back(
//                            object_rotation);
//                        data->at(object_type).scalings.push_back(
//                            object_scaling);
//                        data->at(object_type).brightnesses.push_back(1.0f);
//                        data->at(object_type)
//                        .colorMods.push_back(
//                            glm::vec3(
//                                red_variation, green_variation,
//                                blue_variation));
//                    }
//                }
//            }
            action();
        }
    }
}

Size WorldView::GetWorldAreaSize() const {
    return _<MainScene>().GetWorldAreaSize();
}

RID WorldView::AllocateNewTile() const {
    return _<MainScene>().AllocateNewTile();
}
}
