/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "InstructionsManager.hpp"
#include "Game/Core/Graphics/Rendering/ImageRendering/ImageRenderer.hpp"

namespace JoD {
InstructionsManager::InstructionsManager() {
    for (auto i = 0; i < k_numPreAllocatedÏmages; i++) {
        m_ridsPreAllocatedImages.push_back(
            _<ImageRenderer>().AllocateNewImage());
    }
}

void InstructionsManager::AddImageDrawInstruction(int imageNameHash,
                                                  BoxF area) {
    m_imageDrawInstructions.push_back({imageNameHash, area});
}

void InstructionsManager::PerformInstructions() {}
}
