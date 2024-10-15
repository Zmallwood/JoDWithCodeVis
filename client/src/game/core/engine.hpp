/*
 * Copyright 2024 Andreas Åkerberg.
 */
#pragma once

namespace JoD {
class Engine {
public:
  Engine();
  
  void ResetInputState() const;
  
  void Run();
  
  RID AllocateNewImage() const;
  
  void DrawImage(RID rid, int imageNameHash, const BoxF &area,
                 ColorF color = Colors::White, bool repeatTexture = false,
                 SizeF textureFillAmount = {1.0f, 1.0f},
                 bool noPixelEffect = false) const;
  
  void DrawImage(RID rid, std::string_view imageName, const BoxF &area,
                 ColorF color = Colors::White, bool repeatTexture = false,
                 SizeF textureFillAmount = {1.0f, 1.0f},
                 bool noPixelEffect = false) const;
  
  RID AllocateNewString() const;
  
  void DrawString(int id,
                  std::string_view text,
                  Point2F position,
                  ColorF color = Colors::White,
                  bool centerAlign= false,
                  FontSizes fontSize= FontSizes::_20) const;
  
  RID AllocateNewTile() const;
  
  Size GetWorldAreaSize() const;
  
  void SetCursorStyle(CursorStyles newStyle) const;
  
  bool AnyKeyIsPressed() const;
  
  bool AnyMouseButtonisPressed() const;
  
  GLuint GetImage(int imageNameHash) const;
  
  GLuint GetImage(std::string_view imageName) const;
  
  void CreateBlankImage(std::string uniqueImageName) const;
  
  void SetRunning(bool value) {
    m_running = value;
  }
  
private:
  void Initialize() const;
  
  void PollEvents();
  
  bool m_running{true};
};
}
