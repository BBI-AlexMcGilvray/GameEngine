#include "Pipeline/Rendering/Shaders/ShaderManager.h"

#include "Core/Logging/LogFunctions.h"

#include "Pipeline/Rendering/OpenGL/Headers/ShaderUtils.h"
#include "Pipeline/Rendering/Headers/RenderDataCreator.h"
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
    for (auto& shader : _shaders)
    {
      RenderDataCreator::DestroyRenderData(shader.second, &DestroyShader);
    }
  }
  
  RenderDataHandle ShaderManager::GetDefaultShaderHandle()
  {
    return _defaultShader.GetHandle();
  }
  
  RenderDataHandle ShaderManager::GetDefaultTextureShaderHandle()
  {
    return _textureShader.GetHandle();
  }

  RenderDataHandle ShaderManager::AddShader(const Data::AssetName<Data::Rendering::ShaderData>& shader)
  {
    auto existingShader = _shaders.find(shader);
    if (existingShader != _shaders.end())
    {
      DEBUG_WARNING("Shader Manager", "Trying to add the same shader twice");
      return existingShader->second.GetHandle();
    }

    // doing it this way could give us problems because we don't hold on to shared_ptrs that keep the data alive for shaders/fragmentshaders/vertexshaders
    // i think we want this to have a loop that goes over all shaders (to add them), locks all data when reached, and then releases them all when done
    _shaders[shader] = ShaderData();
    return _shaders[shader].GetHandle();
  }

  const ShaderData& ShaderManager::GetShader(const RenderDataHandle& handle)
  {
    if (_defaultShader.IsHeldBy(handle))
    {
      return _EnsureDefaultIsValid();
    }

    if (_textureShader.IsHeldBy(handle))
    {
      return _EnsureDefaultTextureIsValid();
    }

    auto& existing = std::find_if(_shaders.begin(), _shaders.end(), [this, handle](const std::pair<Data::AssetName<Data::Rendering::ShaderData>, ShaderData>& data)
    {
      return data.second.IsHeldBy(handle);
    });
    if (existing != _shaders.end())
    {
      return _EnsureShaderIsValid(existing->first, existing->second);
    }

    DEBUG_THROW("ShaderManager", "No shader exists for handle!");
    return _EnsureDefaultIsValid();
  }

  const ShaderData& ShaderManager::_EnsureDefaultIsValid()
  {
    if (!_defaultShader.IsValid())
    {
      RenderDataCreator::InitializeRenderData(_defaultShader, &CreateDefaultShader);
    }
    return _defaultShader;
  }

  const ShaderData& ShaderManager::_EnsureDefaultTextureIsValid()
  {
    if (!_textureShader.IsValid())
    {
      RenderDataCreator::InitializeRenderData(_textureShader, &CreateDefaultTextureShader);
    }
    return _textureShader;
  }

  const ShaderData& ShaderManager::_EnsureShaderIsValid(Data::AssetName<Data::Rendering::ShaderData> shaderAssetName, ShaderData& shader)
  {
    auto shaderData = _assetManager.getAssetData(shaderAssetName);
    CreateShader(shader, _assetManager, shaderData);
    return shader;
  }

}// namespace Rendering
}// namespace Application