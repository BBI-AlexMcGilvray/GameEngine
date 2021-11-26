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
    
    // AssetData<FragmentShaderData> in debug?
  };
  
  VertexShader_NEW CreateVertexShader_NEW(const Data::AssetData<Data::Rendering::VertexShaderData>& data);

  // for 'preparing' the shader, all shaders should have the same input variables - so we can do it generically
  struct FragmentShader_NEW
  {
    GLShader glShader;
    
    // AssetData<VertexShaderData> in debug?
  };
  
  FragmentShader_NEW CreateFragmentShader_NEW(const Data::AssetData<Data::Rendering::FragmentShaderData>& data);

  struct Shader_NEW
  {
    VertexShader_NEW vertexShader;
    FragmentShader_NEW fragmentShader;
    GLShaderProgram glProgram;

    // AssetData<ShaderData> in debug?
  };

  Shader_NEW CreateShader_NEW(const Data::AssetData<Data::Rendering::ShaderData>& data);
}// namespace Rendering
}// namespace Application