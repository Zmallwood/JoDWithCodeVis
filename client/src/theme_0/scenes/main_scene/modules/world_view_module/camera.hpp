/*
 * Copyright 2024 Andreas Åkerberg.
 */
#pragma once

namespace JoD {
class Camera {
public:
  Camera();
  
  void Update();
  
  float GetZoomAmount() const;
  
  Point3F MoveCloserToCamera(Point3F originalPoint, float amount) const;
  
  Point3F& GetCameraPositionRef() {
    return m_cameraPosition;
  }
  
  float GetVerticalAngle() const {
    return m_verticalAngle;
  }
  
  float& GetVerticalAngleRef() {
    return m_verticalAngle;
  }
  
  float GetCameraDistance() const {
    return m_cameraDistance;
  }
  
  float GetHorizontalAngle() const {
    return m_horizontalAngle;
  }
  
  float& GetHorizontalAngleRef() {
    return m_horizontalAngle;
  }
  
private:
  void UpdateZooming();
  void CalculateCameraPosition();
  
  Point3F m_playerPosition3D;
  float m_horizontalAngle {0.0f};
  float m_verticalAngle {45.f};
  Point3F m_cameraPosition;
  float m_cameraDistance {150.f};
  
  const float m_zoomSensitivity {0.15f};
  const float m_fov {33.0f};
};
}
