#include "Pipeline/Rendering/OpenGL/Headers/GLShader.h"

namespace Application {
namespace Rendering {
  GLShader::GLShader()
    : GLObject(0, GL_SHADER)
  {}

  GLShader::GLShader(GLuint object, GLenum type)
    : GLObject(object, type)
  {}

  GLShader::~GLShader()
  {
    // this gets called by glDeleteProgram
    //glDeleteShader(Object);
  }
}// namespace Rendering
}// namespace Application