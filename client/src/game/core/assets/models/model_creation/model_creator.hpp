/*
 * Copyright 2024 Andreas Åkerberg
 */
#pragma once

namespace JoD {
class Model;
class ModelPart;

class ModelCreator {
public:
  std::shared_ptr<Model> CreateModel(const aiScene *scene);
  
private:
  std::vector<std::shared_ptr<ModelPart>> GetModelParts(
    const aiScene* scene) const;
  std::map<std::shared_ptr<std::string>,
           std::vector<int>> GetModelMeshIDs(const aiScene* scene) const;
  std::vector<aiMesh*> GetNodeMeshes(const aiScene* scene,
                                     std::vector<int> nodeMeshIDs) const;
  
};
}
