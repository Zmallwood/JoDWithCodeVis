/*
 * Copyright 2024 Andreas Åkerberg.
 */
#pragma once
#include "ImageDrawInstruction.hpp"

namespace JoD {
class InstructionsManager {
public:
  InstructionsManager();
  
  void Clear();
  
  void AddImageDrawInstruction(int imageNameHash, BoxF area);
  
  void PerformInstructions();
  
private:
  std::vector<ImageDrawInstruction> m_imageDrawInstructions;
  std::vector<RID> m_ridsPreAllocatedImages;
  
  inline static int s_ridCounter {0};
  
  const int k_numPreAllocatedÏmages {400};
};
}
