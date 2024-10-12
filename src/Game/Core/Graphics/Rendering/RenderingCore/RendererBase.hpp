/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

#include "BufferTypes.hpp"

namespace JoD {
class ShaderProgram;

class RendererBase {
  protected:
    RendererBase();
    
    GLuint GenNewVAOID();
    
    GLuint GenNewBuffID(BufferTypes buffType, GLuint vaoID);
    
    void SetIndicesData(GLuint indicesVBOID, int numVertices,
                        const void *data) const;
    
    void SetData(GLuint vboID, int numVertices, const void *data,
                 BufferTypes buffType, int layoutLocation = -1) const;
    
    GLuint GetUniformLocation(const std::string &variableName);
    
    void UseVAOBegin(GLuint vaoID) const;
    
    GLuint GetBuffID(BufferTypes buffType, GLuint vaoID) const;
    
    void UpdateIndicesData(GLuint indicesVBOID,
                           std::vector<int> &indices) const;
    
    void UpdateData(GLuint vboID, std::vector<float> &data,
                    BufferTypes buffType,
                    int layoutLocation) const;
    
    void UseVAOEnd() const;
    
    void CleanupBase() const;
    
    auto GetShaderProgram() const {
        return m_shaderProgram;
    }
    
    static constexpr int k_numberVerticesInRectangle{4};
    
  private:
    void SetArrayBufferData(GLuint vboID, int numVertices, const void *data,
                            int numFloatsPerEntry,
                            int layoutLocation = -1) const;
    
    void SetArrayBufferDataInt(GLuint vboID, int numvertices, const void *data,
                               int numFloatsPerEntry,
                               int layoutLocation = -1) const;
    
    void UpdateArrayBufferData(GLuint vboID, std::vector<float> &data,
                               int numFloatsPerEntry, int layoutLocation) const;
    
    void UpdateArrayBufferDataInt(GLuint vboID, std::vector<float> &data,
                                  int numFloatsPerEntry,
                                  int layoutLocation) const;
    
    std::vector<GLuint> m_vaoIDs;
    std::map<BufferTypes, std::map<GLuint, GLuint>> m_vboIDs;
    std::shared_ptr<ShaderProgram> m_shaderProgram;
    inline static const auto k_numFloatsPerEntry = std::map<BufferTypes, int>{
        {BufferTypes::Indices, 1},     {BufferTypes::Positions2D, 2},
        {BufferTypes::Positions3D, 3}, {BufferTypes::Colors, 4},
        {BufferTypes::UVs, 2},         {BufferTypes::Normals, 3},
        {BufferTypes::BoneIDs, 4},     {BufferTypes::Weights, 4}};
};
}
