/*
 * Copyright 2024 Andreas Åkerberg
 */
#include "model_creator.hpp"
#include "game/core/model_structure/model.hpp"
#include "model_part_creator.hpp"

namespace JoD {
std::shared_ptr<Model> ModelCreator::CreateModel(const aiScene *scene) {
  auto anim_duration = scene->mNumAnimations >
                       0 ? scene->mAnimations[0]->mDuration : 0;
  auto new_model = std::make_shared<Model>(anim_duration);
  for (auto &model_part : GetModelParts(scene))
    new_model->modelParts.push_back(model_part);
  return new_model;
}

std::vector<std::shared_ptr<ModelPart>> ModelCreator::GetModelParts(
  const aiScene *scene) const {
  std::vector<std::shared_ptr<ModelPart>> all_model_parts;
  for (auto &entry : GetModelMeshIDs(scene)){
    std::string node_name = *entry.first;
    auto node_mesh_ids = entry.second;
    for (auto &mesh : GetNodeMeshes(scene, node_mesh_ids)){
      auto new_model_part =
        _<ModelPartCreator>().CreateModelPartFromMesh(
          scene, node_name,
          mesh);
      all_model_parts.push_back(new_model_part);
    }
  }
  return all_model_parts;
}

std::map<std::shared_ptr<std::string>,
         std::vector<int>> ModelCreator::GetModelMeshIDs(
  const aiScene *scene) const {
  auto root_node = scene->mRootNode;
  auto num_sub_nodes = root_node->mNumChildren;
  std::map<std::shared_ptr<std::string>,
           std::vector<int>> node_name_to_meshes;
  for (auto i = 0; i < num_sub_nodes; i++){
    auto sub_node = root_node->mChildren[i];
    auto sub_node_name = sub_node->mName;
    auto num_meshes = sub_node->mNumMeshes;
    std::vector<int> meshes;
    for (auto j = 0; j < num_meshes; j++)
      meshes.push_back(sub_node->mMeshes[j]);
    node_name_to_meshes.insert(
      {std::make_shared<std::string>(
         sub_node_name.C_Str()), meshes});
  }
  return node_name_to_meshes;
}

std::vector<aiMesh *>ModelCreator::GetNodeMeshes(const aiScene *scene,
                                                 std::vector<int> nodeMeshIds)
const {
  std::vector<aiMesh *> node_meshes;
  auto num_meshes = nodeMeshIds.size();
  for (auto i = 0; i < num_meshes; i++){
    auto mesh = scene->mMeshes[nodeMeshIds.at(i)];
    node_meshes.push_back(mesh);
  }
  return node_meshes;
}
}
