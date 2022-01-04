#include "Pipeline/Rendering/Shaders/Shader.h"

#include "Pipeline/Headers/ApplicationManager.h"
#include "Pipeline/Rendering/OpenGL/Headers/ShaderUtils.h"

namespace Application {
namespace Rendering {
  VertexShader CreateDefaultVertexShader()
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

  VertexShader CreateVertexShader(const Data::AssetData<Data::Rendering::VertexShaderData>& data)
  {
      return CreateVertexShader(data->shaderCode);
  }

  FragmentShader CreateDefaultFragmentShader()
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

  FragmentShader CreateFragmentShader(const Data::AssetData<Data::Rendering::FragmentShaderData>& data)
  {
      return CreateFragmentShader(data->shaderCode);
  }

  Shader CreateShader(const Data::AssetData<Data::Rendering::ShaderData>& data)
  {
      // to get rid of ApplicationManager dependency, this should probably take in a VertexShader and a FragmentShader as well as the data?
      VertexShader vertex = CreateVertexShader(ApplicationManager::AppAssetManager().getAssetData(data->vertexShader));
      FragmentShader fragment = CreateFragmentShader(ApplicationManager::AppAssetManager().getAssetData(data->fragmentShader));

      return CreateShader(vertex, fragment);
  }
  
  Shader CreateDefaultShader()
  {
      VertexShader defaultVertex = CreateDefaultVertexShader();
      FragmentShader defaultFragment = CreateDefaultFragmentShader();

      return CreateShader(defaultVertex, defaultFragment);
  }
} // namespace Application
} // namespace Rendering