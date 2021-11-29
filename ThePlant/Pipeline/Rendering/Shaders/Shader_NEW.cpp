#include "Pipeline/Rendering/Shaders/Shader_NEW.h"

#include "Pipeline/Headers/ApplicationManager.h"
#include "Pipeline/Rendering/OpenGL/Headers/ShaderUtils.h"

namespace Application {
namespace Rendering {
  VertexShader_NEW CreateVertexShader_NEW(const Data::AssetData<Data::Rendering::VertexShaderData>& data)
  {
      return CreateVertexShader(data->shaderCode);
  }

  FragmentShader_NEW CreateFragmentShader_NEW(const Data::AssetData<Data::Rendering::FragmentShaderData>& data)
  {
      return CreateFragmentShader(data->shaderCode);
  }

  Shader_NEW CreateShader_NEW(const Data::AssetData<Data::Rendering::ShaderData>& data)
  {
      // to get rid of ApplicationManager dependency, this should probably take in a VertexShader and a FragmentShader as well as the data?
      VertexShader_NEW vertex = CreateVertexShader_NEW(ApplicationManager::AppAssetManager().getAssetData(data->vertexShader));
      FragmentShader_NEW fragment = CreateFragmentShader_NEW(ApplicationManager::AppAssetManager().getAssetData(data->fragmentShader));

      return CreateShader(vertex, fragment);
  }
} // namespace Application
} // namespace Rendering