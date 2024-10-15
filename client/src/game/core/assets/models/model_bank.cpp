/*
 * Copyright 2024 Andreas Åkerberg
 */
#include "ModelBank.hpp"
#include "model_creation/ModelCreator.hpp"

namespace JoD {
const Model* ModelBank::GetModel(int modelNameHash) const {
  return m_models.at(modelNameHash).get();
}

std::map<int, std::shared_ptr<const Model>> ModelBank::GetAllModels() const {
  return m_models;
}

void ModelBank::LoadModels() {
  using iterator = std::filesystem::recursive_directory_iterator;
  auto absAllModelsPath = std::string(SDL_GetBasePath()) + k_relModelsPath;
  for (const auto &filePath : iterator(absAllModelsPath)) {
    auto pathStr = filePath.path().string();
    auto extensionPos = pathStr.find_last_of('.') + 1;
    auto fileExtension = pathStr.substr(extensionPos);
    if (fileExtension != "dae")
      continue;
    auto loadedModel = LoadSingleModel(pathStr);
    auto imageNameStart = pathStr.find_last_of('/') + 1;
    auto imageNameWithExt = pathStr.substr(imageNameStart);
    auto imageNameExtPos = imageNameWithExt.find_last_of('.');
    auto fileNameNoExt = imageNameWithExt.substr(0, imageNameExtPos);
    auto imageNameHash = Hash(fileNameNoExt);
    m_models.insert({imageNameHash, loadedModel});
  }
}

std::shared_ptr<Model> ModelBank::LoadSingleModel(std::string_view pathStr) {
  Assimp::Importer importer;
  const aiScene *scene = importer.ReadFile(pathStr.data(), 0);
  return _<ModelCreator>().CreateModel(scene);
}
}
