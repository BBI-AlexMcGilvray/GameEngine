#pragma once

#include <set>
#include <variant>

#include "Core/Headers/CoreDefs.h"

#include "Data/Headers/AssetData.h"
#include "Data/Rendering/Headers/MaterialData.h"
#include "Pipeline/Rendering/Shaders/Shader_NEW.h"

namespace Application {
namespace Rendering {
  using ShaderVariant = std::variant<double, float, int, uint>;
  // <shader attribute name, shader attribute value>
  using ShaderContext = std::set<std::string, ShaderVariant>;

  // holds shader information in terms of how it is affected by light, shadows, ...
  // maybe should contain the data, not BE the data?
  struct Material_NEW
  {
    ShaderContext shaderContext;
    const Shader_NEW& shader;

    Material_NEW(const Shader_NEW& shader)
    : shader(shader)
    {}
  };

  Material_NEW CreateMaterial(const Data::Rendering::MaterialData& data, ShaderManager& shaderManager)
  {
    Material_NEW material(shaderManager.GetShader(data.shader));

    ShaderContext context;
    // visit data for each shader value and create context using variable name and value
    // then get shader from shader manager (create if it doesn't exist)

    return material;
  }
} // namespace Application
} // namespace Rendering