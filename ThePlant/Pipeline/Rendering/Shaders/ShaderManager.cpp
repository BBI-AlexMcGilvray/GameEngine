#include "Pipeline/Rendering/Shaders/ShaderManager.h"

#include "Core/Logging/LogFunctions.h"

#include "Pipeline/Rendering/OpenGL/Headers/ShaderUtils.h"
#include "Pipeline/StateSystem/Headers/State.h"

namespace Application {
namespace Rendering {
  ShaderManager::ShaderManager(Data::AssetManager& assetManager, AssetLoaderFactory& assetLoaderFactory)
  : _assetManager(assetManager)
  , _assetLoaderFactory(assetLoaderFactory)
  {
    _assetLoaderFactory.Register(Core::HashType<Data::Rendering::ShaderData>(), [&](State& state, const Data::AssetName<void>& asset)
    {
      AddShader(asset);
    });
  }

  ShaderManager::~ShaderManager()
  {
    _assetLoaderFactory.Unregister(Core::HashType<Data::Rendering::ShaderData>());

    // if we want to lock the shaders in the asset manager (which we shouldn't need to do - except in debug mode so we can live-edit them) then we should unlock them all here
  }
  
  const Shader ShaderManager::GetDefaultShader()
  {
    // this is here because we can't make it immediately since opengl is not in a good state, but we should have an nicer way to check for validity
    if (_defaultShader.glProgram.Object == 0)
    {
      _defaultShader = CreateDefaultShader();
    }

    return _defaultShader;
  }
  
  const Shader ShaderManager::GetDefaultTextureShader()
  {
    // this is here because we can't make it immediately since opengl is not in a good state, but we should have an nicer way to check for validity
    if (_textureShader.glProgram.Object == 0)
    {
      _textureShader = CreateDefaultTextureShader();
    }

    return _textureShader;
  }

  const Shader ShaderManager::AddShader(const Data::AssetName<Data::Rendering::ShaderData>& shader)
  {
    auto existingShader = _shaders.find(shader);
    if (existingShader != _shaders.end())
    {
      DEBUG_WARNING("Shader Manager", "Trying to add the same shader twice");
      return existingShader->second;
    }

    // doing it this way could give us problems because we don't hold on to shared_ptrs that keep the data alive for shaders/fragmentshaders/vertexshaders
    // i think we want this to have a loop that goes over all shaders (to add them), locks all data when reached, and then releases them all when done
    auto shaderData = _assetManager.getAssetData(shader);
    _shaders[shader] = CreateShader(_assetManager, shaderData);
    return _shaders[shader];
  }

  const Shader ShaderManager::GetShader(const Data::AssetName<Data::Rendering::ShaderData>& shader)
  {
    auto existing = _shaders.find(shader);
    if (existing == _shaders.end())
    {
      return AddShader(shader);
    }

    return existing->second;
  }

}// namespace Rendering
}// namespace Application