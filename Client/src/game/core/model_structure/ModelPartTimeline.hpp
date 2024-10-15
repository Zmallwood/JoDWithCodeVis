/*
 * Copyright 2024 Andreas Åkerberg
 */


namespace JoD {
class ModelPartKeyframe;

class ModelPartTimeline {
  public:
    std::map<float, std::shared_ptr<const ModelPartKeyframe>> keyframes;
};
}
