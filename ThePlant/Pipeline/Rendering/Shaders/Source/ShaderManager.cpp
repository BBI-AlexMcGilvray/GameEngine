#include "Pipeline/Rendering/Shaders/Headers/ShaderManager.h"

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
  }

  void ShaderManager::CleanUp()
  {
    DebugShader.Destroy();
    DefaultShader.Destroy();
    DefaultSkinnedShader.Destroy();
  }
}// namespace Rendering
}// namespace Application