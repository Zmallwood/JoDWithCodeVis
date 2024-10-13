/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "Camera.hpp"
#include "Game/Core/Graphics/Rendering/CameraGL.hpp"
#include "Game/Core/Input/Mouse/MouseInput.hpp"
#include "Game/Core/CoreGameObjects/Player.hpp"
#include "Game/Core/WorldStructure/World.hpp"
#include "Game/Core/WorldStructure/WorldArea.hpp"
#include "Game/Core/WorldStructure/Tile.hpp"
#include "WorldViewConfiguration.hpp"

namespace JoD {
Camera::Camera() {
    CalculateCameraPosition();
}

void Camera::Update() {
    UpdateZooming();
    CalculateCameraPosition();
    auto lookAt = m_playerPosition3D;
    auto playerHeight = 2.0f;
    auto lookFrom = m_cameraPosition;
    lookAt.y += playerHeight;
    lookFrom.y += playerHeight;
    auto usedCameraDistance = m_cameraDistance;
    auto usedFov = m_fov * 7.0f / std::sqrt(usedCameraDistance);
    auto newPerspectiveMatrix =
        glm::perspective(
            glm::radians(usedFov / 2), 1600.0f / 900.0f, 0.1f,
            1000.0f);
    auto newViewMatrix = glm::lookAt(
        glm::vec3(lookFrom.x, lookFrom.y, lookFrom.z),
        glm::vec3(lookAt.x, lookAt.y, lookAt.z), glm::vec3(0.0, 1.0, 0.0));
    _<CameraGL>().SetPerspectiveMatrix(newPerspectiveMatrix);
    _<CameraGL>().SetViewMatrix(newViewMatrix);
}

float Camera::GetZoomAmount() const {
    return m_cameraDistance;
}

void Camera::UpdateZooming() {
    auto mouseWheelDelta = _<MouseInput>().GetMouseWheelDeltaPickResult();
    if (mouseWheelDelta != 0) {
        auto distanceChange = mouseWheelDelta / m_zoomSensitivity;
        m_cameraDistance+= distanceChange;
    }
    m_cameraDistance = std::max(std::min(m_cameraDistance, 250.0f), 2.0f);
}

void Camera::CalculateCameraPosition() {
    auto& player = _<Player>();
    auto& world = _<World>();
    auto usedCameraDistance = m_cameraDistance;
    auto usedVerticalAngle = m_verticalAngle;
    auto playerPositionNoElevation = player.GetPosition3D();
    auto dzUnrotated= CosDegrees(usedVerticalAngle) * usedCameraDistance;
    auto hypotenuse = dzUnrotated;
    auto dx = SinDegrees(m_horizontalAngle) * hypotenuse - 3.0f *
              SinDegrees(m_horizontalAngle);
    auto dz = CosDegrees(m_horizontalAngle) * hypotenuse - 3.0f *
              CosDegrees(m_horizontalAngle);
    auto dy = SinDegrees(usedVerticalAngle) * usedCameraDistance;
    auto dxPlayer = -4.0f * SinDegrees(m_horizontalAngle);
    auto dzPlayer= -4.0f * CosDegrees(m_horizontalAngle);
    auto playerWorldAreaPosition = player.GetMajorCoordinate();
    auto playerPosition = player.GetPosition();
    auto worldArea = world.GetCurrentWorldArea();
    if (worldArea) {
        auto playerTile = worldArea->GetTile(playerPosition.ToIntPoint());
        auto elevAmount = WorldViewConfiguration::k_elevAmount;
        auto tileCoord = playerPosition.ToIntPoint();
        auto tile = worldArea->GetTile(tileCoord);
        auto elev00 = static_cast<float>(tile->GetElevation());
        auto elev10 = elev00;
        auto elev11 = elev00;
        auto elev01 = elev00;
        auto coord10 = tileCoord.Translate(1, 0);
        auto coord11 = tileCoord.Translate(1, 1);
        auto coord01 = tileCoord.Translate(0, 1);
        if (worldArea->IsValidCoordinate(coord10))
            elev10 = worldArea->GetTile(coord10)->GetElevation();
        if (worldArea->IsValidCoordinate(coord11))
            elev11 = worldArea->GetTile(coord11)->GetElevation();
        if (worldArea->IsValidCoordinate(coord01))
            elev01 = worldArea->GetTile(coord01)->GetElevation();
        auto tileAvgElev = (elev00 + elev10 + elev01 + elev11) / 4.0f;
        auto playerTileDx =
            playerPosition.x - static_cast<int>(playerPosition.x) - 0.5f;
        auto playerTileDy =
            playerPosition.y - static_cast<int>(playerPosition.y) - 0.5f;
        auto elevDx = ((elev10 - elev00) + (elev11 - elev01)) / 2.0f;
        auto elevDy = ((elev01 - elev00) + (elev11 - elev10)) / 2.0f;
        auto playerElev =
            tileAvgElev + playerTileDx * elevDx + playerTileDy *
            elevDy;
        m_playerPosition3D = playerPositionNoElevation.Translate(
            dxPlayer, playerElev * elevAmount, dzPlayer);
        m_cameraPosition =
            playerPositionNoElevation.Translate(
                dx,
                dy + playerElev * elevAmount, dz);
    }
}

Point3F Camera::MoveCloserToCamera(Point3F original_point, float amount) const {
    auto cameraDx = (float)m_cameraPosition.x - original_point.x;
    auto cameraDz = (float)m_cameraPosition.z - original_point.z;
    auto radius = std::sqrt(cameraDx * cameraDx + cameraDz * cameraDz);
    return {
        original_point.x + cameraDx / radius * amount, original_point.y,
        original_point.z + cameraDz / radius * amount};
}
}
