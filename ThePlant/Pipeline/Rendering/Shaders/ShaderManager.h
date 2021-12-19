#pragma once

#include <unordered_map>

#include "Data/Rendering/Headers/ShaderData.h"
#include "Data/Headers/AssetManager.h"

#include "Pipeline/Rendering/Shaders/Shader_NEW.h"

namespace Application {
namespace Rendering {
  // holds list of ALL shaders that can be used, handles construction, retrieval and deletion of the shaders
  class ShaderManager
  {
  public:
    ShaderManager(Data::AssetManager& assetManager);
    ~ShaderManager();

    // games should loop through all shaders and add them at game-creation time (once games get big enough, this would get done on level-switch?)
    const Shader_NEW AddShader(const Data::AssetName<Data::Rendering::ShaderData>& shader);
    const Shader_NEW GetShader(const Data::AssetName<Data::Rendering::ShaderData>& shader); // we probably want to return a straight shader, but need to be ensure lifetime is ensured

  private:
    Data::AssetManager& _assetManager;
    std::unordered_map<Data::AssetName<Data::Rendering::ShaderData>, Shader_NEW, Data::AssetNameHasher<Data::Rendering::ShaderData>> _shaders;
  };
}// namespace Rendering
}// namespace Application