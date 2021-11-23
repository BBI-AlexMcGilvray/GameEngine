#pragma once

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
  };
  
  // for 'preparing' the shader, all shaders should have the same input variables - so we can do it generically
  struct FragmentShader_NEW
  {
    GLShader glShader;
  };

  struct Shader_NEW
  {
    GLShaderProgram glProgram;
  };
}// namespace Rendering
}// namespace Application