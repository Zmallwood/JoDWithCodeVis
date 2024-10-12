/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

#include "Graphics/Rendering/TextRendering/FontSizes.hpp"

namespace JoD {
class Engine {
  public:
    Engine();
    
    void Initialize();
    
    void Run();
    
    RID NewImage();
    
    void DrawImage(RID rid, int imageNameHash, const BoxF &area,
                   ColorF color = Colors::White, bool repeatTexture = false,
                   SizeF textureFillAmount = {1.0f, 1.0f},
                   bool noPixelEffect = false);
    
    void DrawImage(RID rid, std::string_view imageName, const BoxF &area,
                   ColorF color = Colors::White, bool repeatTexture = false,
                   SizeF textureFillAmount = {1.0f, 1.0f},
                   bool noPixelEffect = false);
    
    RID NewString();
    
    void DrawString(int id,
                    std::string_view text,
                    Point2F position,
                    ColorF color = Colors::White,
                    bool centerAlign= false,
                    FontSizes fontSize= FontSizes::_20);
    
    Size GetWorldAreaSize();
    
    void SetRunning(bool value) {
        m_running = value;
    }
    
  private:
    void PollEvents();
    
    bool m_running{true};
};
}
