/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

namespace JoD {
class CameraGL {
  public:
    auto GetPerspectiveMatrix() {
        return m_perspectiveMatrix;
    }
    
    auto GetViewMatrix() {
        return m_viewMatrix;
    }
    
    void SetPerspectiveMatrix(glm::mat4 value) {
        m_perspectiveMatrix = value;
    }
    
    void SetViewMatrix(glm::mat4 value) {
        m_viewMatrix = value;
    }
    
  private:
    glm::mat4 m_perspectiveMatrix;
    glm::mat4 m_viewMatrix;
};
}
