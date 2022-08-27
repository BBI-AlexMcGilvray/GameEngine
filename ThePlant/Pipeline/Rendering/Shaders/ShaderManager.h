#pragma once

#include <unordered_map>

#include "Data/Rendering/Headers/ShaderData.h"
#include "Data/Headers/AssetManager.h"

#include "Pipeline/AssetHandling/AssetLoaderFactory.h"
#include "Pipeline/Rendering/Shaders/Shader.h"

namespace Application {
namespace Rendering {
  // holds list of ALL shaders that can be used, handles construction, retrieval and deletion of the shaders
  class ShaderManager
  {
  public:
    ShaderManager(Data::AssetManager& assetManager, AssetLoaderFactory& assetLoaderFactory);
    ~ShaderManager();

    // games should loop through all shaders and add them at game-creation time (once games get big enough, this would get done on level-switch?)
    const Shader GetDefaultShader();
    const Shader AddShader(const Data::AssetName<Data::Rendering::ShaderData>& shader);
    const Shader GetShader(const Data::AssetName<Data::Rendering::ShaderData>& shader); // we probably want to return a straight shader, but need to be ensure lifetime is ensured

  private:
    Data::AssetManager& _assetManager;
    AssetLoaderFactory& _assetLoaderFactory;
    
    Shader _defaultShader;
    std::unordered_map<Data::AssetName<Data::Rendering::ShaderData>, Shader, Data::AssetNameHasher<Data::Rendering::ShaderData>> _shaders;
  };
}// namespace Rendering
}// namespace Application