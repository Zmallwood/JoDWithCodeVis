/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

namespace JoD {
class Model;

class ModelBank {
  public:
    const Model* GetModel(int modelNameHash) const;
    
    std::map<int, std::shared_ptr<const Model>> GetAllModels() const;
    
    void LoadModels();
    
  private:
    std::shared_ptr<Model> LoadSingleModel(std::string_view pathStr);
    
    std::map<int, std::shared_ptr<const Model>> m_models;
    
    const std::string k_relModelsPath {"Resources/Models/"};
};
}
