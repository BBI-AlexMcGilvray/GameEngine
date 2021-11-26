#include "Pipeline/Rendering/Shaders/Headers/ShaderManager.h"

#include "Core/Logging/Logger.h"

#include "Pipeline/Headers/ApplicationManager.h"
#include "Pipeline/Rendering/OpenGL/Headers/ShaderUtils.h"

namespace Application {
namespace Rendering {
  ShaderManager::ShaderManager()
  {
  }

  ShaderManager::~ShaderManager()
  {
  }

  Ptr<const ObjectShaderBase> ShaderManager::GetShader(ObjectShaderType shader) const
  {
    switch (shader) {
    case ObjectShaderType::Debug: {
      return &DebugShader;
    }
    case ObjectShaderType::Default: {
      return &DefaultShader;
    }
    case ObjectShaderType::SkinnedDefault: {
      return &DefaultSkinnedShader;
    }
    default:
      return &DefaultShader;
    }
  }

  void ShaderManager::Initialize()
  {
    DebugShader.Initialize();
    DefaultShader.Initialize();
    DefaultSkinnedShader.Initialize();

    // should this be where we register/lock all shaders (see comment below)?
  }

  void ShaderManager::CleanUp()
  {
    DebugShader.Destroy();
    DefaultShader.Destroy();
    DefaultSkinnedShader.Destroy();

    for (auto shader : _shaders)
    {
      DeleteShader(shader.second);
    }
  }
  
  const Shader_NEW ShaderManager::AddShader(const Data::AssetName<Data::Rendering::ShaderData>& shader)
  {
    if (_shaders.find(shader) != _shaders.end())
    {
      DEBUG_WARNING("Shader Manager", "Trying to add the same shader twice");
      return;
    }

    // doing it this way could give us problems because we don't hold on to shared_ptrs that keep the data alive for shaders/fragmentshaders/vertexshaders
    // i think we want this to have a loop that goes over all shaders (to add them), locks all data when reached, and then releases them all when done
    auto shaderData = ApplicationManager::AppAssetManager().getAssetData(shader);
    _shaders[shader] = CreateShader_NEW(shaderData);
    return _shaders[shader];
  }

  const Shader_NEW ShaderManager::GetShader(const Data::AssetName<Data::Rendering::ShaderData>& shader)
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