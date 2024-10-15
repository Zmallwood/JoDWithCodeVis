/*
 * Copyright 2024 Andreas Åkerberg.
 */
#pragma once
#include "IScene.hpp"

namespace JoD {
class SceneEngine {
public:
  void InitializeScenes();
  
  void UpdateCurrentScene();
  
  void RenderCurrentScene();
  
  void GoToScene(std::string_view newSceneName);
  
  Size GetWorldAreaSize() const;
  
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
  
  bool AnyMouseButtonIsPressed() const;
  
  bool AnyKeyIsPressed() const;
  
  void StopEngine();
  
private:
  void AddScene(std::string_view sceneName, IScene& scene);
  
  std::map<int, IScene &> m_scenes;
  int m_currentScene{0};
};
}
