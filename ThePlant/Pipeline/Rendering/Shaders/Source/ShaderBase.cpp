#include "Pipeline/Rendering/Shaders/Headers/ShaderBase.h"

namespace Application {
namespace Rendering {
  ShaderBase::ShaderBase(Ptr<const char> shaderName)
    : GLShader(0, GL_SHADER), ShaderName(shaderName)
  {}

  ShaderBase::ShaderBase(Ptr<const char> shaderName, GLenum shaderType)
    : GLShader(0, shaderType), ShaderName(shaderName)
  {}

  void ShaderBase::SetShaderProgram(GLuint program)
  {
    Object = program;
  }
}// namespace Rendering
}// namespace Application