/*
 * Copyright 2024 Andreas Åkerberg
 */
#include "model_part_creator.hpp"
#include "game/core/model_structure/model_part.hpp"
#include "game/core/model_structure/model_part_keyframe.hpp"
#include "game/core/model_structure/model_part_timeline.hpp"
#include "model_part_keyframe_creator.hpp"

namespace JoD {
std::shared_ptr<ModelPart> ModelPartCreator::CreateModelPartFromMesh(
  const aiScene *scene, std::string nodeName, aiMesh *mesh) const {
  auto new_model_part = std::make_shared<ModelPart>();
  auto tex_name_hash = GetTexNameHashForMesh(scene, mesh);
  new_model_part->texNameHash = tex_name_hash;
  auto no_keyframe_at_time_0_exists =
    _<ModelPartKeyframeCreator>().GetPositionKeyframe(
      scene, nodeName,
      0).mTime > 0;
  auto num_keyframes =
    _<ModelPartKeyframeCreator>().GetNodePositionKeyframes(
      scene,
      nodeName).size();
  for (auto k = 0; k < num_keyframes; k++){
    auto position_keyframe =
      _<ModelPartKeyframeCreator>().GetPositionKeyframe(
        scene,
        nodeName, k);
    auto rotation_keyframe =
      _<ModelPartKeyframeCreator>().GetRotationKeyframe(
        scene,
        nodeName, k);
    auto scaling_keyframe =
      _<ModelPartKeyframeCreator>().GetScalingKeyframe(
        scene, nodeName,
        k);
    auto keyframe_time = static_cast<float>(position_keyframe.mTime);
    auto new_model_part_keyframe = GetNewModelPartKeyframe(
      scene, nodeName, mesh, position_keyframe, rotation_keyframe,
      scaling_keyframe);
    new_model_part->timeline->keyframes[keyframe_time] =
      new_model_part_keyframe;
//        new_model_part->timeline->keyframes.insert(
//            {keyframe_time,
//             new_model_part_keyframe});
    if (no_keyframe_at_time_0_exists && k == 0)
      new_model_part->timeline->keyframes[0.0f] = new_model_part_keyframe;
    //new_model_part->timeline->keyframes.insert({0.0f,
    //                                            new_model_part_keyframe});
  }
  return new_model_part;
}

int ModelPartCreator::GetTexNameHashForMesh(const aiScene *scene,
                                            aiMesh *mesh) const {
  auto texture_name_hashcodes = GetTexNameHashcodes(scene);
  auto material = mesh->mMaterialIndex;
  auto texture_name_hash = texture_name_hashcodes.at(material);
  return texture_name_hash;
}

std::shared_ptr<ModelPartKeyframe> ModelPartCreator::GetNewModelPartKeyframe(
  const aiScene *scene, std::string nodeName, aiMesh *mesh,
  aiVectorKey positionKeyFrame,
  aiQuatKey rotationKeyFrame, aiVectorKey scalingKeyFrame) const {
  auto new_model_part_keyframe = std::make_shared<ModelPartKeyframe>();
  auto node_transformation = GetNodeTransformation(scene, nodeName);
  auto num_vertices = mesh->mNumVertices;
  for (auto i = 0; i < num_vertices; i++){
    auto mesh_vertex = mesh->mVertices[i];
    auto mesh_normal = mesh->mNormals[i];
    auto mesh_uv = mesh->mTextureCoords[0][i];
    auto position = GetPosition(
      mesh_vertex, node_transformation, positionKeyFrame,
      rotationKeyFrame,
      scalingKeyFrame);
    auto color = ColorF{0.0f, 0.0f, 0.0f, 0.0f};
    auto normal = GetPosition(
      mesh_normal, node_transformation, positionKeyFrame,
      rotationKeyFrame,
      scalingKeyFrame);
    auto uv = Point2F{1.0f - mesh_uv.x, 1.0f - mesh_uv.y};
    Vertex3F anim_vertex;
    anim_vertex.position = position;
    anim_vertex.color = color;
    anim_vertex.normal = normal;
    anim_vertex.uv = uv;
    new_model_part_keyframe->vertices.push_back(anim_vertex);
  }
  return new_model_part_keyframe;
}

std::vector<int> ModelPartCreator::GetTexNameHashcodes(
  const aiScene *scene) const {
  std::vector<int> texture_name_hashcodes;
  auto num_materials = scene->mNumMaterials;
  for (auto i = 0; i < num_materials; i++){
    aiString texture_name_cstr;
    scene->mMaterials[i]->Get(
      AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), texture_name_cstr);
    auto texture_name = std::string(texture_name_cstr.C_Str());
    auto texture_name_no_extension = texture_name.substr(
      0,
      texture_name.length()
      - 4);
    auto texture_name_hash = Hash(texture_name_no_extension);
    texture_name_hashcodes.push_back(texture_name_hash);
  }
  return texture_name_hashcodes;
}

aiMatrix4x4 ModelPartCreator::GetNodeTransformation(const aiScene *scene,
                                                    std::string nodeName) const
{
  auto all_transformations = GetTransformations(scene);
  for (auto &alpha : all_transformations){
    if (*alpha.first == nodeName.data())
      return alpha.second;
  }
  return aiMatrix4x4();
}

Point3F ModelPartCreator::GetPosition(
  aiVector3D vertex, aiMatrix4x4 node_transformation,
  aiVectorKey positionKeyFrame,
  aiQuatKey rotationKeyFrame, aiVectorKey scalingKeyFrame) const {
  aiVector3D ai_position = {vertex.x, vertex.y, vertex.z};
  ai_position.x *= scalingKeyFrame.mValue.x;
  ai_position.y *= scalingKeyFrame.mValue.y;
  ai_position.z *= scalingKeyFrame.mValue.z;
  ai_position = rotationKeyFrame.mValue.GetMatrix() * ai_position;
  ai_position = node_transformation * ai_position;
  auto position = Point3F{ai_position.x, ai_position.y, ai_position.z};
  Translate(&position, positionKeyFrame);
  ai_position = {position.x, position.y, position.z};
  position = {ai_position.x, ai_position.y, ai_position.z};
  float temp;
  temp = position.y;
  position.y = position.z;
  position.z = temp;
  return position;
}

std::map<std::shared_ptr<std::string>,
         aiMatrix4x4> ModelPartCreator::GetTransformations(
  const aiScene *scene) const {
  auto root_node = scene->mRootNode;
  auto num_nodes = root_node->mNumChildren;
  auto node_name_to_transformations = std::map<std::shared_ptr<std::string>,
                                               aiMatrix4x4>();
  for (auto i = 0; i < num_nodes; i++){
    auto node = root_node->mChildren[i];
    auto node_name = node->mName;
    auto node_transformation = node->mTransformation;
    node_name_to_transformations.insert(
      {std::make_shared<std::string>(node_name.C_Str()),
       node_transformation});
  }
  return node_name_to_transformations;
}

void ModelPartCreator::Translate(Point3F *position,
                                 aiVectorKey positionKeyFrame) const {
  auto translation_matrix = aiMatrix4x4();
  translation_matrix[0][3] = positionKeyFrame.mValue.x;
  translation_matrix[1][3] = positionKeyFrame.mValue.y;
  translation_matrix[2][3] = positionKeyFrame.mValue.z;
  translation_matrix[0][0] = 1;
  translation_matrix[1][1] = 1;
  translation_matrix[2][2] = 1;
  translation_matrix[3][3] = 1;
  auto ai_position = aiVector3D{position->x, position->y, position->z};
  ai_position = translation_matrix * ai_position;
  *position = {-ai_position.x, ai_position.y, ai_position.z};
}
}
