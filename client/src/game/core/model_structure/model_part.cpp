/*
 * Copyright 2024 Andreas Åkerberg
 */
#include "model_part.hpp"
#include "model_part_timeline.hpp"

namespace JoD {
ModelPart::ModelPart()
  : timeline(std::make_shared<ModelPartTimeline>()) {}
}
