/*
 * Copyright 2024 Andreas Åkerberg
 */
#pragma once

namespace JoD {
class ModelPart;

class Model {
public:
  Model(int animDuration);
  
  std::vector<std::shared_ptr<const ModelPart>> modelParts;
  
  const int animDuration;
};
}
