#pragma once

#include <set>
#include <variant>

#include "Core/Headers/CoreDefs.h"
#include "Core/Math/Headers/Color.h"

#include "Data/Headers/AssetData.h"
#include "Data/Rendering/Headers/MaterialData.h"
#include "Pipeline/Rendering/Shaders/Shader_NEW.h"

namespace Application {
namespace Rendering {
  class ShaderManager;

  using ShaderVariant = std::variant<double, float, int, uint, Core::Math::Color>; // others will probably be needed (vectors, matrices, ...)
  // <shader attribute name, shader attribute value>
  using ShaderContext = std::set<std::pair<std::string, ShaderVariant>>;

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

  Material_NEW CreateMaterial(const Data::AssetData<Data::Rendering::MaterialData>& data, ShaderManager& shaderManager);
} // namespace Application
} // namespace Rendering