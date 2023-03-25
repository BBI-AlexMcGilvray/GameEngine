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

    RenderDataHandle GetDefaultShaderHandle(); // feels like this should not be a method, should reference by name or something
    RenderDataHandle GetDefaultTextureShaderHandle(); // feels like this should not be a method, should reference by name or something
    // games should loop through all shaders and add them at game-creation time (once games get big enough, this would get done on level-switch?)
    RenderDataHandle AddShader(const Data::AssetName<Data::Rendering::ShaderData>& shader);
    const ShaderData& GetShader(const RenderDataHandle& handle); // we probably want to return a straight shader, but need to be ensure lifetime is ensured
    // NOTE:
    /*
      we have nothing that removes a shader, if we add one we will need to look at how we will handle using shaders in a threaded context!
    */

  private:
    Data::AssetManager& _assetManager;
    AssetLoaderFactory& _assetLoaderFactory;
    
    ShaderData _defaultShader; // should be referenced by name?
    ShaderData _textureShader; // should be referenced by name?
    std::unordered_map<Data::AssetName<Data::Rendering::ShaderData>, ShaderData, Data::AssetNameHasher<Data::Rendering::ShaderData>> _shaders;

    const ShaderData& _EnsureDefaultIsValid();
    const ShaderData& _EnsureDefaultTextureIsValid();
    const ShaderData& _EnsureShaderIsValid(Data::AssetName<Data::Rendering::ShaderData> shaderAssetName, ShaderData& shader);
  };
}// namespace Rendering
}// namespace Application