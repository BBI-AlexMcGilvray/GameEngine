#pragma once

#include "Data/Headers/AssetData.h"
#include "Data/Headers/AssetManager.h"
#include "Data/Rendering/Headers/ShaderData.h"

#include "Pipeline/Rendering/Headers/RenderData.h"
#include "Pipeline/Rendering/OpenGL/Headers/GLShader.h"
#include "Pipeline/Rendering/OpenGL/Headers/GLShaderProgram.h"

namespace Application {
namespace Rendering {
  /*
  Shaders are not responsible for deleting themselves, the shader manager will need to do that
    - Shader manager should be a map of name->program
  Shader manager must also delete the fragment and vertex shaders
    - Shader manager should also have a map of name->program, this will also help us avoid compiling the same shader multiple times
      - Since different shaders can share vertex/fragment shaders, we should only have one of each and they only get deleted at the end/once everything is compiled
  */

  // for 'preparing' the shader, all shaders should have the same input variables - so we can do it generically
  struct VertexShader
  {
    GLShader glShader;
    
    // maybe not the AssetData<...>, but AssetName<...>? Because AssetData will hold onto a shared_ptr and could affect lifetime
    // AssetData<VertexShaderData> in debug?

    VertexShader() = default;
    VertexShader(const VertexShader&) = default;
    VertexShader& operator=(const VertexShader&) = default;

    bool operator==(const VertexShader& other) const
    {
      return (glShader == other.glShader);
    }
  };
  
  VertexShader CreateVertexShader(const Data::AssetData<Data::Rendering::VertexShaderData>& data);

  // for 'preparing' the shader, all shaders should have the same input variables - so we can do it generically
  struct FragmentShader
  {
    GLShader glShader;
    
    // maybe not the AssetData<...>, but AssetName<...>? Because AssetData will hold onto a shared_ptr and could affect lifetime
    // AssetData<FragmentShaderData> in debug?

    FragmentShader() = default;
    FragmentShader(const FragmentShader&) = default;
    FragmentShader& operator=(const FragmentShader&) = default;

    bool operator==(const FragmentShader& other) const
    {
      return (glShader == other.glShader);
    }
  };
  
  FragmentShader CreateFragmentShader(const Data::AssetData<Data::Rendering::FragmentShaderData>& data);

  struct ShaderData : TRenderData<ShaderData>
  {
    VertexShader vertexShader;
    FragmentShader fragmentShader;
    GLShaderProgram glProgram;

    // maybe not the AssetData<...>, but AssetName<...>? Because AssetData will hold onto a shared_ptr and could affect lifetime
    // AssetData<ShaderData> in debug?

    ShaderData() = default;
    ShaderData(ShaderData&&) = default;
    ShaderData& operator=(ShaderData&&) = default;
    
    ShaderData(const ShaderData&) = delete;
    ShaderData& operator=(const ShaderData&) = delete;

    bool operator==(const ShaderData& other) const
    {
      return (vertexShader == other.vertexShader && fragmentShader == other.fragmentShader && glProgram == other.glProgram);
    }
  };

  void CreateShader(ShaderData& shader, Data::AssetManager& assetManager, const Data::AssetData<Data::Rendering::ShaderData>& data);
  void CreateDefaultShader(ShaderData& shader);
  void CreateDefaultTextureShader(ShaderData& shader);
  void DestroyShader(ShaderData& shader);
}// namespace Rendering
}// namespace Application