#pragma once

#include <unordered_map>

#include "Data/Rendering/Headers/ShaderData.h"

#include "Pipeline/Rendering/Shaders/Shader_NEW.h"

#include "DebugObjectShader.h"
#include "ObjectShader.h"
#include "SkinnedObjectShader.h"

namespace Application {
namespace Rendering {
  // holds list of ALL shaders that can be used, handles construction, retrieval and deletion of the shaders
  class ShaderManager
  {
  public:
    // Leave for now, old
    enum class ObjectShaderType {
      Debug,
      Default,
      SkinnedDefault
    };

    DebugObjectShader DebugShader;
    ObjectShader DefaultShader;
    SkinnedObjectShader DefaultSkinnedShader;

    Ptr<const ObjectShaderBase> GetShader(ObjectShaderType shader) const;

    void Initialize();
    void CleanUp();
    // \old

    ShaderManager();
    ~ShaderManager();

    const Shader_NEW AddShader(const Data::AssetName<Data::Rendering::ShaderData>& shader);
    const Shader_NEW GetShader(const Data::AssetName<Data::Rendering::ShaderData>& shader); // we probably want to return a straight shader, but need to be ensure lifetime is ensured

  private:
    std::unordered_map<Data::AssetName<Data::Rendering::ShaderData>, Shader_NEW> _shaders;
  };
}// namespace Rendering
}// namespace Application