#include "InstructionsManager.hpp"
#include "game/core/graphics/rendering/image_rendering/ImageRenderer.hpp"

namespace JoD {
InstructionsManager::InstructionsManager() {
    for (auto i = 0; i < k_numPreAllocatedÏmages; i++) {
        m_ridsPreAllocatedImages.push_back(
            _<ImageRenderer>().AllocateNewImage());
    }
}

void InstructionsManager::Clear() {
    m_imageDrawInstructions.clear();
    s_ridCounter = 0;
}

void InstructionsManager::AddImageDrawInstruction(int imageNameHash,
                                                  BoxF area) {
    m_imageDrawInstructions.push_back({imageNameHash, area});
}

void InstructionsManager::PerformInstructions() {
    for (auto entry : m_imageDrawInstructions) {
        
        auto rid = m_ridsPreAllocatedImages[s_ridCounter];
        
        _<ImageRenderer>().DrawImage(rid, entry.imageNameHash, entry.area);
        
        s_ridCounter++;
    }
}
}
