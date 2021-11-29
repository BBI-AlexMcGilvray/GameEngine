#pragma once

#include <unordered_set>
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
  using ShaderVariable = std::pair<std::string, ShaderVariant>;

  struct ShaderContextHasher
  {
    ShaderContextHasher() = default;

    std::size_t operator()(const ShaderVariable& variable) const
    {
      return _stringHasher(variable.first);
    }

  private:
    std::hash<std::string> _stringHasher;
  };

  // <shader attribute name, shader attribute value>
  using ShaderContext = std::unordered_set<ShaderVariable, ShaderContextHasher>;

  // holds shader information in terms of how it is affected by light, shadows, ...
  // maybe should contain the data, not BE the data?
  struct Material_NEW
  {
    ShaderContext shaderContext;
    const Shader_NEW shader;

    Material_NEW(const Shader_NEW& shader)
    : shader(shader)
    {}
  };

  Material_NEW CreateMaterial(const Data::AssetData<Data::Rendering::MaterialData>& data, ShaderManager& shaderManager);
} // namespace Application
} // namespace Rendering