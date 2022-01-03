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

  struct ShaderVariableHasher
  {
    ShaderVariableHasher() = default;

    std::size_t operator()(const ShaderVariable& variable) const
    {
      return _stringHasher(variable.first);
    }

  private:
    std::hash<std::string> _stringHasher;
  };

  // <shader attribute name, shader attribute value>
  using ShaderContext = std::unordered_set<ShaderVariable, ShaderVariableHasher>;

  // holds shader information in terms of how it is affected by light, shadows, ...
  // maybe should contain the data, not BE the data?
  struct Material_NEW
  {
    ShaderContext shaderContext;
    Shader_NEW shader;

    // maybe not the AssetData<...>, but AssetName<...>? Because AssetData will hold onto a shared_ptr and could affect lifetime
    // AssetData<MaterialData> in debug?

    Material_NEW() = default;
    Material_NEW(const Material_NEW& other) = default;
    Material_NEW& operator=(const Material_NEW& other) = default;

    bool operator==(const Material_NEW& other) const
    {
      return (shaderContext == other.shaderContext && shader == other.shader);
    }
  };

  Material_NEW CreateDefaultMaterial(ShaderManager& shaderManager);
  Material_NEW CreateMaterial(const Data::AssetData<Data::Rendering::MaterialData>& data, ShaderManager& shaderManager);
} // namespace Application
} // namespace Rendering