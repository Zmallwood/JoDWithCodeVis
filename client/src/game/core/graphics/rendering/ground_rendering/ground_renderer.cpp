/*
 * Copyright 2024 Andreas Åkerberg.
 */
#include "GroundRenderer.hpp"
#include "game/core/graphics/rendering/rendering_core/ShaderProgram.hpp"
#include "shader_ground/ShaderGroundVertex.hpp"
#include "shader_ground/ShaderGroundFragment.hpp"
#include "game/core/graphics/rendering/CameraGL.hpp"
#include "game/core/core_game_objects/Player.hpp"
#include "game/core/graphics/GraphicsGL.hpp"
#include "game/core/Engine.hpp"

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

RID GroundRenderer::AllocateNewImagePolygon(int numVertices) {
  if (numVertices <= 2)
    throw std::invalid_argument(
            CodeLocation() +
            "numVertices must be > 2 to form a valid polygon.");
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

RID GroundRenderer::AllocateNewTile() {
  return AllocateNewImagePolygon(4);
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
  auto indexBufferID = GetBuffID(BufferTypes::Indices, vaoId);
  auto positionBufferID = GetBuffID(BufferTypes::Positions3D, vaoId);
  auto colorBufferID = GetBuffID(BufferTypes::Colors, vaoId);
  auto uvBufferID = GetBuffID(BufferTypes::UVs, vaoId);
  auto normalBufferID = GetBuffID(BufferTypes::Normals, vaoId);
  glBindVertexArray(vaoId);
  UpdateIndicesData(indexBufferID, indices);
  UpdateData(
    positionBufferID, positions, BufferTypes::Positions3D,
    k_LocationPosition);
  UpdateData(colorBufferID, colors, BufferTypes::Colors, k_LocationColor);
  UpdateData(uvBufferID, uvs, BufferTypes::UVs, k_LocationUv);
  UpdateData(
    normalBufferID, normals, BufferTypes::Normals,
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
  glm::vec3 viewPos(
    _<Player>().GetPosition3D().x, _<Player>().GetPosition3D().y,
    _<Player>().GetPosition3D().z);
  glUniform3fv(m_locationViewPos, 1, glm::value_ptr(viewPos));
  glm::vec3 fogColorGL(
    _<GraphicsGL>().GetFogColorGround().r,
    _<GraphicsGL>().GetFogColorGround().g,
    _<GraphicsGL>().GetFogColorGround().b);
  glUniform3fv(m_locationFogColor, 1, glm::value_ptr(fogColorGL));
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
    glm::vec3 viewPos(
      _<Player>().GetPosition3D().x, _<Player>().GetPosition3D().y,
      _<Player>().GetPosition3D().z);
    glUniform3fv(m_locationViewPos, 1, glm::value_ptr(viewPos));
    glm::vec3 fogColorGL(
      _<GraphicsGL>().GetFogColorGround().r,
      _<GraphicsGL>().GetFogColorGround().g,
      _<GraphicsGL>().GetFogColorGround().b);
    glUniform3fv(m_locationFogColor, 1, glm::value_ptr(fogColorGL));
    glUseProgram(GetShaderProgram()->GetProgramID());
  }
  auto imageID = _<Engine>().GetImage(imageNameHash);
  glBindTexture(GL_TEXTURE_2D, imageID);
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
