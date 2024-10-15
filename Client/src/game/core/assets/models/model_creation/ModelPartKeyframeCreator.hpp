/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

namespace JoD {
class ModelPartKeyframeCreator {
  public:
    aiVectorKey GetPositionKeyframe(const aiScene *, std::string, int) const;
    aiQuatKey GetRotationKeyframe(const aiScene *, std::string, int) const;
    aiVectorKey GetScalingKeyframe(const aiScene *, std::string, int) const;
    std::vector<aiVectorKey> GetNodePositionKeyframes(const aiScene *,
                                                      std::string) const;
    std::vector<aiQuatKey> GetNodeRotationKeyframes(const aiScene *,
                                                    std::string) const;
    std::vector<aiVectorKey> GetNodeScalingKeyframes(const aiScene *,
                                                     std::string) const;
    
  private:
    std::map<std::string,
             std::vector<aiVectorKey>> GetAnimPositionKeyframes(
        const aiScene *) const;
    std::map<std::string,
             std::vector<aiQuatKey>> GetAnimRotationKeyframes(
        const aiScene *) const;
    std::map<std::string,
             std::vector<aiVectorKey>> GetAnimScalingKeyframes(
        const aiScene *) const;
};
}
