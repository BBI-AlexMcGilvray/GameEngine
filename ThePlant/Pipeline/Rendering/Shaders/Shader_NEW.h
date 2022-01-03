#pragma once

#include "Data/Headers/AssetData.h"
#include "Data/Rendering/Headers/ShaderData.h"

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
  struct VertexShader_NEW
  {
    GLShader glShader;
    
    // maybe not the AssetData<...>, but AssetName<...>? Because AssetData will hold onto a shared_ptr and could affect lifetime
    // AssetData<VertexShaderData> in debug?

    VertexShader_NEW() = default;
    VertexShader_NEW(const VertexShader_NEW&) = default;
    VertexShader_NEW& operator=(const VertexShader_NEW&) = default;

    bool operator==(const VertexShader_NEW& other) const
    {
      return (glShader == other.glShader);
    }
  };
  
  VertexShader_NEW CreateVertexShader_NEW(const Data::AssetData<Data::Rendering::VertexShaderData>& data);

  // for 'preparing' the shader, all shaders should have the same input variables - so we can do it generically
  struct FragmentShader_NEW
  {
    GLShader glShader;
    
    // maybe not the AssetData<...>, but AssetName<...>? Because AssetData will hold onto a shared_ptr and could affect lifetime
    // AssetData<FragmentShaderData> in debug?

    FragmentShader_NEW() = default;
    FragmentShader_NEW(const FragmentShader_NEW&) = default;
    FragmentShader_NEW& operator=(const FragmentShader_NEW&) = default;

    bool operator==(const FragmentShader_NEW& other) const
    {
      return (glShader == other.glShader);
    }
  };
  
  FragmentShader_NEW CreateFragmentShader_NEW(const Data::AssetData<Data::Rendering::FragmentShaderData>& data);

  struct Shader_NEW
  {
    VertexShader_NEW vertexShader;
    FragmentShader_NEW fragmentShader;
    GLShaderProgram glProgram;

    // maybe not the AssetData<...>, but AssetName<...>? Because AssetData will hold onto a shared_ptr and could affect lifetime
    // AssetData<ShaderData> in debug?

    Shader_NEW() = default;
    Shader_NEW(const Shader_NEW&) = default;
    Shader_NEW& operator=(const Shader_NEW&) = default;

    bool operator==(const Shader_NEW& other) const
    {
      return (vertexShader == other.vertexShader && fragmentShader == other.fragmentShader && glProgram == other.glProgram);
    }
  };

  Shader_NEW CreateShader_NEW(const Data::AssetData<Data::Rendering::ShaderData>& data);
  Shader_NEW CreateDefaultShader();
}// namespace Rendering
}// namespace Application