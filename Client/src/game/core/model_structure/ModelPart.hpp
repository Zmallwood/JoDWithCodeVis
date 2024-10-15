/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

namespace JoD {
class ModelPartTimeline;

class ModelPart {
  public:
    ModelPart();
    
    int texNameHash;
    std::shared_ptr<ModelPartTimeline> timeline;
};
}
