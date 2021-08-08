#include "Pipeline/Rendering/OpenGL/Headers/GLShaderProgram.h"

namespace Application {
namespace Rendering {
  GLShaderProgram::GLShaderProgram()
    : GLObject(0, GL_PROGRAM)
  {}

  GLShaderProgram::GLShaderProgram(GLuint object, GLenum type)
    : GLObject(object, type)
  {}

  GLShaderProgram::~GLShaderProgram()
  {
    // this needs to be deleted WHILE THE GL CONTEXT IS STILL ACTIVE
    // glDeleteProgram(Object);
  }
}// namespace Rendering
}// namespace Application