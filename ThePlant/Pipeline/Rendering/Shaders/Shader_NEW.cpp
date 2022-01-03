#include "Pipeline/Rendering/Shaders/Shader_NEW.h"

#include "Pipeline/Headers/ApplicationManager.h"
#include "Pipeline/Rendering/OpenGL/Headers/ShaderUtils.h"

namespace Application {
namespace Rendering {
  VertexShader_NEW CreateDefaultVertexShader()
  {
      static const std::string defaultShaderCode = R"(
        #version 450 core
			
        // values per vertex
        layout(location = 0) in vec3 vPosition;

        // Values that stay constant for the whole mesh
        uniform mat4 MVP;
        uniform vec4 modColor;

        // values to return
        out vec4 Color;

        void main()
        {
            Color = modColor;
            
            gl_Position = MVP * vec4(vPosition, 1.0);
        }
      )";
      return CreateVertexShader(defaultShaderCode);
  }

  VertexShader_NEW CreateVertexShader_NEW(const Data::AssetData<Data::Rendering::VertexShaderData>& data)
  {
      return CreateVertexShader(data->shaderCode);
  }

  FragmentShader_NEW CreateDefaultFragmentShader()
  {
      static const std::string defaultShaderCode = R"(
        #version 450 core
			
        layout(location = 0) out vec4 fColor;

        // values passed from vertex shader
        in vec4 Color;

        // Values that stay constant for the whole mesh

        void main()
        {
            fColor = Color;
        }
      )";
      return CreateFragmentShader(defaultShaderCode);
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
  
  Shader_NEW CreateDefaultShader()
  {
      VertexShader_NEW defaultVertex = CreateDefaultVertexShader();
      FragmentShader_NEW defaultFragment = CreateDefaultFragmentShader();

      return CreateShader(defaultVertex, defaultFragment);
  }
} // namespace Application
} // namespace Rendering