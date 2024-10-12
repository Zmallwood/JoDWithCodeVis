/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

namespace JoD {
class ShaderProgram {
  public:
    bool Create(const GLchar *vertexShaderSource,
                const GLchar *fragmentShaderSource);
    
    void Cleanup() const;
    
    GLuint GetProgramID() const {
        return m_programID;
    }
    
  private:
    GLuint CompileShader(const GLchar *shaderSource, GLuint *shader,
                         GLenum shaderType) const;
    
    GLuint m_programID = 0;
};
}
