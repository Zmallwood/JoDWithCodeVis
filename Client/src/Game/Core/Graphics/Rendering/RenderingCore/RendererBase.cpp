/*
 * Copyright 2024 Andreas Åkerberg.
 */

#include "RendererBase.hpp"
#include "ShaderProgram.hpp"

namespace JoD {
RendererBase::RendererBase()
    : m_shaderProgram(std::make_shared<ShaderProgram>()) {}

GLuint RendererBase::GenNewVAOID() {
    GLuint vaoID;
    glGenVertexArrays(1, &vaoID);
    m_vaoIDs.push_back(vaoID);
    return vaoID;
}

GLuint RendererBase::GenNewBuffID(BufferTypes buffType, GLuint vaoID) {
    GLuint buffID;
    glGenBuffers(1, &buffID);
    m_vboIDs[buffType][vaoID] = buffID;
    return buffID;
}

void RendererBase::SetIndicesData(GLuint indicesVBOID, int numVertices,
                                  const void *data) const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesVBOID);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        numVertices * k_numFloatsPerEntry.at(BufferTypes::Indices) *
        sizeof(float),
        data, GL_DYNAMIC_DRAW);
}

void RendererBase::SetData(GLuint vboID, int numVertices, const void *data,
                           BufferTypes buffType, int layoutLocation) const {
    if (buffType == BufferTypes::BoneIDs)
        SetArrayBufferDataInt(
            vboID, numVertices, data,
            k_numFloatsPerEntry.at(buffType), layoutLocation);
    else
        SetArrayBufferData(
            vboID, numVertices, data,
            k_numFloatsPerEntry.at(buffType), layoutLocation);
}

GLuint RendererBase::GetUniformLocation(const std::string &variableName) const {
    return glGetUniformLocation(
        m_shaderProgram->GetProgramID(),
        variableName.c_str());
}

void RendererBase::UseVAOBegin(GLuint vaoID) const {
    glUseProgram(m_shaderProgram->GetProgramID());
    glBindVertexArray(vaoID);
}

GLuint RendererBase::GetBuffID(BufferTypes buffType, GLuint vaoID) const {
    return m_vboIDs.at(buffType).at(vaoID);
}

void RendererBase::UpdateIndicesData(GLuint indicesVBOID,
                                     std::vector<int> &indices) const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesVBOID);
    glBufferSubData(
        GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(float) * indices.size(),
        indices.data());
}

void RendererBase::UpdateData(GLuint vboID, std::vector<float> &data,
                              BufferTypes buffType, int layoutLocation) const {
    if (buffType == BufferTypes::BoneIDs)
        UpdateArrayBufferDataInt(
            vboID, data, k_numFloatsPerEntry.at(buffType),
            layoutLocation);
    else
        UpdateArrayBufferData(
            vboID, data, k_numFloatsPerEntry.at(buffType),
            layoutLocation);
}

void RendererBase::UseVAOEnd() const {
    glBindVertexArray(0);
    glUseProgram(0);
}

void RendererBase::CleanupBase() const {
    for (auto &buffType : m_vboIDs)
        for (auto &bufferEntry : buffType.second)
            glDeleteBuffers(1, &bufferEntry.second);
    for (auto vaoID : m_vaoIDs)
        glDeleteVertexArrays(1, &vaoID);
    m_shaderProgram->Cleanup();
}

void RendererBase::SetArrayBufferData(GLuint vboID, int numVertices,
                                      const void *data, int numFloatsPerEntry,
                                      int layoutLocation) const {
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(
        GL_ARRAY_BUFFER, numVertices * numFloatsPerEntry * sizeof(float),
        data, GL_DYNAMIC_DRAW);
    if (layoutLocation >= 0) {
        glVertexAttribPointer(
            layoutLocation, numFloatsPerEntry, GL_FLOAT, GL_FALSE,
            0, (const GLvoid *)0);
        glEnableVertexAttribArray(layoutLocation);
    }
}

void RendererBase::SetArrayBufferDataInt(GLuint vboID, int numvertices,
                                         const void *data,
                                         int numFloatsPerEntry,
                                         int layoutLocation) const {
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(
        GL_ARRAY_BUFFER, numvertices * numFloatsPerEntry * sizeof(int),
        data, GL_DYNAMIC_DRAW);
    if (layoutLocation >= 0) {
        glEnableVertexAttribArray(3);
        glVertexAttribIPointer(
            layoutLocation, numFloatsPerEntry, GL_INT, 0,
            (const GLvoid *)0);
        glEnableVertexAttribArray(layoutLocation);
    }
}

void RendererBase::UpdateArrayBufferData(GLuint vboID, std::vector<float> &data,
                                         int numFloatsPerEntry,
                                         int layoutLocation) const {
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferSubData(
        GL_ARRAY_BUFFER, 0, sizeof(float) * data.size(),
        data.data());
    glVertexAttribPointer(
        layoutLocation, numFloatsPerEntry, GL_FLOAT, GL_FALSE,
        0, (const GLvoid *)0);
    glEnableVertexAttribArray(layoutLocation);
}

void RendererBase::UpdateArrayBufferDataInt(GLuint vboID,
                                            std::vector<float> &data,
                                            int numFloatsPerEntry,
                                            int layoutLocation) const {
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(int) * data.size(), data.data());
    glVertexAttribIPointer(
        layoutLocation, numFloatsPerEntry, GL_INT, 0,
        (const GLvoid *)0);
    glEnableVertexAttribArray(layoutLocation);
}
}
