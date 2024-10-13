/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "MouseRotation.hpp"
#include "Theme0/Scenes/MainScene/Modules/WorldViewModule/Camera.hpp"
#include "Game/Core/Input/Mouse/MouseInput.hpp"

namespace JoD {
void MouseRotation::Update() {
//    if (Camera::Get()->camera_distance_ == 2.0f) {
//        Cursor::Get()->SavePosition();
//        Cursor::Get()->LockMousePos();
//    }
//    MouseInput ::Get()->GetRightButton().AddFiredAction(
//        "StartRotateCameraAndPlayer",
//        [&] {
//            m_currentRotationType = RotationTypes::CameraAndPlayer;
//            Cursor::Get()->SavePosition();
//            Cursor::Get()->LockMousePos();
//            Cursor::Get()->SetCursorType(CursorTypes::Rotating);
//        },
//        2, 0);
//    MouseInput::Get()->GetRightButton().AddReleasedAction(
//        "StopRotateCameraAndPlayer",
//        [&] {
//            m_currentRotationType = RotationTypes::None;
//            Cursor::Get()->UnlockMousePos();
//            Cursor::Get()->SetCursorType(CursorTypes::Normal);
//        },
//        5, 0, true);
//    MouseInput::Get()->GetMiddleButton().AddFiredAction(
//        "StartRotateOnlyCamera",
//        [&] {
//            m_currentRotationType = RotationTypes::OnlyCamera;
//            Cursor::Get()->SavePosition();
//            Cursor::Get()->LockMousePos();
//            Cursor::Get()->SetCursorType(CursorTypes::Rotating);
//        },
//        14);
//    MouseInput::Get()->GetMiddleButton().AddReleasedAction(
//        "StopRotateOnlyCamera",
//        [&] {
//            m_currentRotationType = RotationTypes::None;
//            Cursor::Get()->UnlockMousePos();
//            Cursor::Get()->SetCursorType(CursorTypes::Normal);
//        },
//        5);
    m_currentRotationType = RotationTypes::OnlyCamera;
    UpdateRotationInProgress();
}

void MouseRotation::UpdateRotationInProgress() const {
    if (m_currentRotationType!= RotationTypes::None ||
        _<Camera>().GetCameraDistance() == 2.0f) {
        auto canvasSize = GetCanvasSize();
        auto motionDelta = _<MouseInput>().GetMotionDeltaPickResult();
        auto deltaX =
            -static_cast<float>(motionDelta.x) * k_rotationSensitivity /
            canvasSize.width;
        auto deltaY=
            static_cast<float>(motionDelta.y) * k_rotationSensitivity /
            canvasSize.height;
        _<Camera>().GetHorizontalAngleRef() += deltaX;
        _<Camera>().GetVerticalAngleRef() =
            std::min(
                std::max(_<Camera>().GetVerticalAngle() + deltaY, -5.0f),
                75.0f);
//        if (m_currentRotationType == RotationTypes::CameraAndPlayer ||
//            _<Camera>().GetCameraDistance() == 2.0f)
//            Player::Get()->SetFacingAngle(Camera::Get()->horizontal_angle_);
//        Cursor::Get()->RestoreSavedPosition();
    }
}
}
