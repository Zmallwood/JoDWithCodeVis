/*
 * Copyright 2024 Andreas Åkerberg
 */
#include "ModelPart.hpp"
#include "ModelPartTimeline.hpp"

namespace JoD {
ModelPart::ModelPart()
  : timeline(std::make_shared<ModelPartTimeline>()) {}
}
