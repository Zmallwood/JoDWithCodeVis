/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

#include "Game/Core/Graphics/Rendering/RenderingCore/RendererBase.hpp"

namespace JoD {
class ImageRenderer : public RendererBase {
  public:
    ImageRenderer();
    
    ~ImageRenderer();
    
    RID AllocateNewImage();
    
    void DrawImage(RID rid, int imageNameHash, const BoxF &area,
                   ColorF color = Colors::White, bool repeatTexture = false,
                   SizeF textureFillAmount = {1.0f, 1.0f},
                   bool noPixelEffect = false) const;
    
    void DrawImage(RID rid, std::string_view imageName, const BoxF &area,
                   ColorF color = Colors::White, bool repeatTexture = false,
                   SizeF textureFillAmount = {1.0f, 1.0f},
                   bool noPixelEffect = false) const;
    
  private:
    int m_locationNoPixelEffect{-1};
    
    static constexpr int k_locationPosition{0};
    static constexpr int k_locationColor{1};
    static constexpr int k_locationUV{2};
};
}
