#include "Pipeline/Rendering/Shaders/Shader.h"

#include "Pipeline/Headers/ApplicationManager.h"
#include "Pipeline/Rendering/OpenGL/Headers/ShaderUtils.h"

namespace Application {
namespace Rendering {
  VertexShader CreateDefaultVertexShader()
  {
    const std::string defaultShaderCode = R"(
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
    return CreateVertexShader(std::move(defaultShaderCode));
  }

  VertexShader CreateDefaultTextureVertexShader()
  {
    const std::string defaultShaderCode = R"(
        #version 450 core
			
        layout (location = 0) in vec3 vPos;
        layout (location = 1) in vec3 vNormals;
        layout (location = 2) in vec2 vTexCoords;

        out vec2 fTexCoords;

        void main()
        {
            gl_Position = vec4(vPos.x, vPos.y, 0.0, 1.0); 
            fTexCoords = vTexCoords;
        }  
      )";
    return CreateVertexShader(std::move(defaultShaderCode));
  }

  VertexShader CreateVertexShader(const Data::AssetData<Data::Rendering::VertexShaderData>& data)
  {
      return CreateVertexShader(data->shaderCode);
  }

  // problem: this is created via the memory tracker (it is instantiated after the tracker is assigned)
  // but it is not destroyed until program end (static), so the tracker is not around at that point...
  // either need to not have the string be static (create a local FragmentShader instead), or have it be untracked
  FragmentShader CreateDefaultFragmentShader()
  {
    const std::string textureShaderCode = R"(
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
    return CreateFragmentShader(std::move(textureShaderCode));
  }

  FragmentShader CreateDefaultTextureFragmentShader()
  {
    const std::string textureShaderCode = R"(
        #version 450 core
			
        layout(location = 0) out vec4 fColor;
  
        in vec2 fTexCoords;

        uniform sampler2D screenTexture;

        void main()
        { 
            vec3 texColour = texture(screenTexture, fTexCoords).xyz;
            fColor = vec4(texColour, 1.0f);
        }
      )";
    return CreateFragmentShader(std::move(textureShaderCode));
  }

  FragmentShader CreateFragmentShader(const Data::AssetData<Data::Rendering::FragmentShaderData>& data)
  {
      return CreateFragmentShader(data->shaderCode);
  }

  void CreateShader(ShaderData& shader, Data::AssetManager& assetManager, const Data::AssetData<Data::Rendering::ShaderData>& data)
  {
      // to get rid of ApplicationManager dependency, this should probably take in a VertexShader and a FragmentShader as well as the data?
      VertexShader vertex = CreateVertexShader(assetManager.getAssetData(data->vertexShader));
      FragmentShader fragment = CreateFragmentShader(assetManager.getAssetData(data->fragmentShader));

      CreateShader(shader, vertex, fragment);
  }
  
  void CreateDefaultShader(ShaderData& shader)
  {
      VertexShader defaultVertex = CreateDefaultVertexShader();
      FragmentShader defaultFragment = CreateDefaultFragmentShader();

      CreateShader(shader, defaultVertex, defaultFragment);
  }

  void CreateDefaultTextureShader(ShaderData& shader)
  {
      VertexShader textureVertex = CreateDefaultTextureVertexShader();
      FragmentShader textureFragment = CreateDefaultTextureFragmentShader();

      CreateShader(shader, textureVertex, textureFragment);
  }

  void DestroyShader(ShaderData& shader)
  {
    DeleteShader(shader);
  }
} // namespace Application
} // namespace Rendering