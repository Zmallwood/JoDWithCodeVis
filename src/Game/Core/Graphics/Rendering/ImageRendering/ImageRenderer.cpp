/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "ImageRenderer.hpp"
#include "Game/Core/Assets/Images/ImageBank.hpp"
#include "Game/Core/Graphics/Rendering/RenderingCore/ShaderProgram.hpp"
#include "Shader/ShaderImagesFragment.hpp"
#include "Shader/ShaderImagesVertex.hpp"

namespace JoD {
ImageRenderer::ImageRenderer() {
    GetShaderProgram()->Create(shaderImagesVertex, shaderImagesFragment);
    m_locationNoPixelEffect = GetUniformLocation("noPixelEffect");
}

ImageRenderer::~ImageRenderer() {
    CleanupBase();
}

RID ImageRenderer::NewImage() {
    auto rid = GenNewVAOID();
    UseVAOBegin(rid);
    auto indexBuffID = GenNewBuffID(BufferTypes::Indices, rid);
    auto posBuffID = GenNewBuffID(BufferTypes::Positions2D, rid);
    auto colorBuffID = GenNewBuffID(BufferTypes::Colors, rid);
    auto uvBuffID = GenNewBuffID(BufferTypes::UVs, rid);
    SetIndicesData(indexBuffID, k_numberVerticesInRectangle, nullptr);
    SetData(
        posBuffID, k_numberVerticesInRectangle, nullptr,
        BufferTypes::Positions2D);
    SetData(
        colorBuffID, k_numberVerticesInRectangle, nullptr,
        BufferTypes::Colors);
    SetData(uvBuffID, k_numberVerticesInRectangle, nullptr, BufferTypes::UVs);
    UseVAOEnd();
    
    return rid;
}

void ImageRenderer::DrawImage(RID rid, int imageNameHash, const BoxF &area,
                              ColorF color, bool repeatTexture,
                              SizeF textureFillAmount, bool noPixelEffect) {
    auto glBox = area.ToGLBoxF();
    Vertex2F verts[k_numberVerticesInRectangle];
    verts[0].position = {glBox.x, glBox.y - glBox.height};
    verts[1].position = {glBox.x, glBox.y};
    verts[2].position = {glBox.x + glBox.width, glBox.y};
    verts[3].position = {glBox.x + glBox.width, glBox.y - glBox.height};
    verts[0].uv = {0.0f, 1.0f / textureFillAmount.height};
    verts[1].uv = {0.0f, 0.0f};
    verts[2].uv = {1.0f / textureFillAmount.width, 0.0f};
    verts[3].uv = {1.0f / textureFillAmount.width,
                   1.0f / textureFillAmount.height};
    glDisable(GL_DEPTH_TEST);
    
    auto imageID = _<ImageBank>().GetImage(imageNameHash);
    
    glBindTexture(GL_TEXTURE_2D, imageID);
    auto indices = std::vector<int>(k_numberVerticesInRectangle);
    std::iota(std::begin(indices), std::end(indices), 0);
    std::vector<float> positions;
    std::vector<float> colors;
    std::vector<float> uvs;
    
    for (auto &vert : verts) {
        positions.push_back(vert.position.x);
        positions.push_back(vert.position.y);
        colors.push_back(color.r);
        colors.push_back(color.g);
        colors.push_back(color.b);
        colors.push_back(color.a);
        uvs.push_back(vert.uv.x);
        uvs.push_back(vert.uv.y);
    }
    UseVAOBegin(rid);
    glUniform1f(m_locationNoPixelEffect, noPixelEffect ? 1.0f : 0.0f);
    auto indexBuffID = GetBuffID(BufferTypes::Indices, rid);
    auto posBuffID = GetBuffID(BufferTypes::Positions2D, rid);
    auto colorBuffID = GetBuffID(BufferTypes::Colors, rid);
    auto uvBuffID = GetBuffID(BufferTypes::UVs, rid);
    UpdateIndicesData(indexBuffID, indices);
    UpdateData(
        posBuffID, positions, BufferTypes::Positions2D,
        k_locationPosition);
    UpdateData(colorBuffID, colors, BufferTypes::Colors, k_locationColor);
    UpdateData(uvBuffID, uvs, BufferTypes::UVs, k_locationUV);
    glDrawElements(
        GL_TRIANGLE_FAN, k_numberVerticesInRectangle, GL_UNSIGNED_INT,
        NULL);
    UseVAOEnd();
}

void ImageRenderer::DrawImage(RID rid, std::string_view imageName,
                              const BoxF &area, ColorF color,
                              bool repeatTexture, SizeF textureFillAmount,
                              bool noPixelEffect) {
    DrawImage(
        rid, Hash(imageName), area, color, repeatTexture, textureFillAmount,
        noPixelEffect);
}
}
