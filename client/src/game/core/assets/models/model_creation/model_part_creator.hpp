/*
 * Copyright 2024 Andreas Åkerberg
 */
#pragma once

namespace JoD {
class ModelPart;
class ModelPartKeyframe;

class ModelPartCreator {
public:
  std::shared_ptr<ModelPart> CreateModelPartFromMesh(const aiScene *,
                                                     std::string,
                                                     aiMesh *) const;
  
private:
  int GetTexNameHashForMesh(const aiScene *, aiMesh *) const;
  std::shared_ptr<ModelPartKeyframe> GetNewModelPartKeyframe(
    const aiScene *, std::string, aiMesh *, aiVectorKey, aiQuatKey,
    aiVectorKey) const;
  std::vector<int> GetTexNameHashcodes(const aiScene *) const;
  aiMatrix4x4 GetNodeTransformation(const aiScene *, std::string) const;
  Point3F GetPosition(aiVector3D, aiMatrix4x4, aiVectorKey, aiQuatKey,
                      aiVectorKey) const;
  std::map<std::shared_ptr<std::string>,
           aiMatrix4x4> GetTransformations(const aiScene *) const;
  void Translate(Point3F *, aiVectorKey) const;
};
}
