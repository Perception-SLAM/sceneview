// Copyright [2015] Albert Huang

#include "sceneview/material_resource.hpp"

#include <vector>

namespace sv {

MaterialResource::MaterialResource(const QString& name,
    ShaderResource::Ptr shader) :
  name_(name),
  shader_(shader),
  shader_parameters_() {
}

template<typename ValueType>
void SUMapSet(ShaderUniformMap* psu_map, const QString& name, ValueType val) {
  ShaderUniformMap& su_map = *psu_map;
  auto iter = su_map.find(name);
  if (iter != su_map.end()) {
    iter->second.Set(val);
  } else {
    su_map[name] = ShaderUniform(name);
    su_map[name].Set(val);
  }
}

void MaterialResource::SetParam(const QString& name, int val) {
  SUMapSet(&shader_parameters_, name, val);
}

void MaterialResource::SetParam(const QString& name,
    const std::vector<int>& val) {
  SUMapSet(&shader_parameters_, name, val);
}

void MaterialResource::SetParam(const QString& name, float val) {
  SUMapSet(&shader_parameters_, name, val);
}

void MaterialResource::SetParam(const QString& name, float val1, float val2) {
  SUMapSet(&shader_parameters_, name, std::vector<float>({val1, val2}));
}

void MaterialResource::SetParam(const QString& name,
    float val1, float val2, float val3) {
  SUMapSet(&shader_parameters_, name, std::vector<float>({val1, val2, val3}));
}

void MaterialResource::SetParam(const QString& name,
    float val1, float val2, float val3, float val4) {
  SUMapSet(&shader_parameters_, name, std::vector<float>(
        {val1, val2, val3, val4}));
}

void MaterialResource::SetParam(const QString& name,
    const std::vector<float>& val) {
  SUMapSet(&shader_parameters_, name, val);
}

void MaterialResource::SetParam(const QString& name, const QMatrix4x4& value) {
  SUMapSet(&shader_parameters_, name, value);
}

void MaterialResource::AddTexture(const QString& name,
    const MaterialResource::TexturePtr& texture) {
  if (texture == nullptr) {
    auto iter = textures_.find(name);
    if (iter != textures_.end()) {
      textures_.erase(iter);
    }
  } else {
    textures_[name] = texture;
  }
}

void MaterialResource::SetTwoSided(bool two_sided) {
  two_sided_ = two_sided;
}

}  // namespace sv
