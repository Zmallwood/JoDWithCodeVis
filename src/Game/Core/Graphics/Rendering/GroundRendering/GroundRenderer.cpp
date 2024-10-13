/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "GroundRenderer.hpp"
#include "Game/Core/Graphics/Rendering/RenderingCore/ShaderProgram.hpp"
#include "ShaderGround/ShaderGroundVertex.hpp"
#include "ShaderGround/ShaderGroundFragment.hpp"
#include "Game/Core/Graphics/Rendering/CameraGL.hpp"
#include "Game/Core/CoreGameObjects/Player.hpp"
#include "Game/Core/Graphics//GraphicsGL.hpp"
#include "Game/Core/Engine.hpp"

namespace JoD {
GroundRenderer::GroundRenderer() {
    GetShaderProgram()->Create(shaderGroundVertex, shaderGroundFragment);
    m_locationProjection= GetUniformLocation("projection");
    m_locationView= GetUniformLocation("view");
    m_locationModel= GetUniformLocation("model");
    m_locationAlpha= GetUniformLocation("mAlpha");
    m_locationViewPos= GetUniformLocation("viewPos");
    m_locationFogColor= GetUniformLocation("fogColor");
}

RID GroundRenderer::AllocNewImagePolygon(int numVertices) {
    auto vaoID= GenNewVAOID();
    auto indexBuffID = GenNewBuffID(
        BufferTypes::Indices,
        vaoID);
    auto positionBuffID= GenNewBuffID(
        BufferTypes::Positions3D,
        vaoID);
    auto colorBuffID= GenNewBuffID(
        BufferTypes::Colors,
        vaoID);
    auto uvBuffID= GenNewBuffID(BufferTypes::UVs, vaoID);
    auto normalBuffID= GenNewBuffID(
        BufferTypes::Normals,
        vaoID);
    glUseProgram(GetShaderProgram()->GetProgramID());
    SetIndicesData(indexBuffID, numVertices, nullptr);
    SetData(positionBuffID, numVertices, nullptr, BufferTypes::Positions3D);
    SetData(colorBuffID, numVertices, nullptr, BufferTypes::Colors);
    SetData(uvBuffID, numVertices, nullptr, BufferTypes::UVs);
    SetData(normalBuffID, numVertices, nullptr, BufferTypes::Normals);
    glBindVertexArray(0);
    glUseProgram(0);
    return vaoID;
}

RID GroundRenderer::AllocNewTile() {
    return AllocNewImagePolygon(4);
}

void GroundRenderer::SetGeometryTile(
    RID vaoId, Vertex3F &v0, Vertex3F &v1, Vertex3F &v2, Vertex3F &v3,
    Point3F &normal00,
    Point3F &normal10, Point3F &normal11, Point3F &normal01) const {
    std::vector<Vertex3F> vertices;
    v0.normal = normal00;
    v1.normal = normal10;
    v2.normal = normal11;
    v3.normal = normal01;
    vertices.push_back(v0);
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);
    SetGeometryImagePolygon(vaoId, vertices);
}

void GroundRenderer::DrawTile(int imageNameHash, RID vaoId,
                              bool depthTestOff) const {
    DrawImagePolygon(imageNameHash, vaoId, 4, depthTestOff);
}

void GroundRenderer::UpdateDrawTile(
    int imageNameHash, RID vaoId, Vertex3F &v0, Vertex3F &v1, Vertex3F &v2,
    Vertex3F &v3,
    Point3F &normal00, Point3F &normal10, Point3F &normal11, Point3F &normal01,
    bool depthTestOff) const {
    std::vector<Vertex3F> vertices;
    v0.normal = normal00;
    v1.normal = normal10;
    v2.normal = normal11;
    v3.normal = normal01;
    vertices.push_back(v0);
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);
    SetGeometryImagePolygon(vaoId, vertices);
    DrawImagePolygon(imageNameHash, vaoId, 4, depthTestOff);
}

void GroundRenderer::SetGeometryImagePolygon(RID vaoId,
                                             std::vector<Vertex3F> &vertices)
const {
    if (!m_isBatchDrawing)
        glUseProgram(GetShaderProgram()->GetProgramID());
    std::vector<int> indices(vertices.size());
    std::iota(std::begin(indices), std::end(indices), 0);
    std::vector<float> positions;
    std::vector<float> colors;
    std::vector<float> uvs;
    std::vector<float> normals;
    for (auto &vertex : vertices) {
        positions.push_back(vertex.position.x);
        positions.push_back(vertex.position.y);
        positions.push_back(vertex.position.z);
        colors.push_back(vertex.color.r);
        colors.push_back(vertex.color.g);
        colors.push_back(vertex.color.b);
        colors.push_back(vertex.color.a);
        uvs.push_back(vertex.uv.x);
        uvs.push_back(vertex.uv.y);
        auto vertex_normal = vertex.normal;
        normals.push_back(vertex_normal.x);
        normals.push_back(vertex_normal.y);
        normals.push_back(vertex_normal.z);
    }
    auto index_buffer_id = GetBuffID(BufferTypes::Indices, vaoId);
    auto position_buffer_id = GetBuffID(BufferTypes::Positions3D, vaoId);
    auto color_buffer_id = GetBuffID(BufferTypes::Colors, vaoId);
    auto uv_buffer_id = GetBuffID(BufferTypes::UVs, vaoId);
    auto normal_buffer_id = GetBuffID(BufferTypes::Normals, vaoId);
    glBindVertexArray(vaoId);
    UpdateIndicesData(index_buffer_id, indices);
    UpdateData(
        position_buffer_id, positions, BufferTypes::Positions3D,
        k_LocationPosition);
    UpdateData(color_buffer_id, colors, BufferTypes::Colors, k_LocationColor);
    UpdateData(uv_buffer_id, uvs, BufferTypes::UVs, k_LocationUv);
    UpdateData(
        normal_buffer_id, normals, BufferTypes::Normals,
        k_LocationNormal);
    glBindVertexArray(0);
    if (!m_isBatchDrawing)
        glUseProgram(0);
}

void GroundRenderer::StartBatchDrawing() {
    m_isBatchDrawing = true;
    glUseProgram(GetShaderProgram()->GetProgramID());
    glUniformMatrix4fv(
        m_locationProjection, 1, GL_FALSE,
        glm::value_ptr(_<CameraGL>().GetPerspectiveMatrix()));
    glUniformMatrix4fv(
        m_locationView, 1, GL_FALSE,
        glm::value_ptr(_<CameraGL>().GetViewMatrix()));
    glm::mat4 model(1.0);
    glUniformMatrix4fv(m_locationModel, 1, GL_FALSE, glm::value_ptr(model));
    glUniform1f(m_locationAlpha, 1.0f);
    glm::vec3 view_pos(
        _<Player>().GetPosition3D().x, _<Player>().GetPosition3D().y,
        _<Player>().GetPosition3D().z);
    glUniform3fv(m_locationViewPos, 1, glm::value_ptr(view_pos));
    glm::vec3 fog_color_gl(
        _<GraphicsGL>().GetFogColorGround().r,
        _<GraphicsGL>().GetFogColorGround().g,
        _<GraphicsGL>().GetFogColorGround().b);
    glUniform3fv(m_locationFogColor, 1, glm::value_ptr(fog_color_gl));
    glUseProgram(GetShaderProgram()->GetProgramID());
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
}

void GroundRenderer::StopBatchDrawing() {
    m_isBatchDrawing = false;
    glUseProgram(0);
    glDisable(GL_CULL_FACE);
}

void GroundRenderer::DrawImagePolygon(
    int imageNameHash, RID vaoId, int vertexCount,
    bool depthTestOff) const {
    if (depthTestOff)
        glDisable(GL_DEPTH_TEST);
    else
        glEnable(GL_DEPTH_TEST);
    if (!m_isBatchDrawing) {
        glUseProgram(GetShaderProgram()->GetProgramID());
        glUniformMatrix4fv(
            m_locationProjection, 1, GL_FALSE,
            glm::value_ptr(_<CameraGL>().GetPerspectiveMatrix()));
        glUniformMatrix4fv(
            m_locationView, 1, GL_FALSE,
            glm::value_ptr(_<CameraGL>().GetViewMatrix()));
        glm::mat4 model(1.0);
        glUniformMatrix4fv(
            m_locationModel, 1, GL_FALSE,
            glm::value_ptr(model));
        glUniform1f(m_locationAlpha, 1.0f);
        glm::vec3 view_pos(
            _<Player>().GetPosition3D().x, _<Player>().GetPosition3D().y,
            _<Player>().GetPosition3D().z);
        glUniform3fv(m_locationViewPos, 1, glm::value_ptr(view_pos));
        glm::vec3 fog_color_gl(
            _<GraphicsGL>().GetFogColorGround().r,
            _<GraphicsGL>().GetFogColorGround().g,
            _<GraphicsGL>().GetFogColorGround().b);
        glUniform3fv(m_locationFogColor, 1, glm::value_ptr(fog_color_gl));
        glUseProgram(GetShaderProgram()->GetProgramID());
    }
    auto imageId = _<Engine>().GetImage(imageNameHash);
    glBindTexture(GL_TEXTURE_2D, imageId);
    glBindVertexArray(vaoId);
    glDrawElements(GL_TRIANGLE_FAN, vertexCount, GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);
    if (!m_isBatchDrawing)
        glUseProgram(0);
}

void GroundRenderer::Cleanup() const {
    CleanupBase();
}
}
