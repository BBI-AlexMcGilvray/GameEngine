#pragma once

#include "GLObject.h"

namespace Application {
namespace Rendering {
  struct GLShader : GLObject
  {
    GLShader();
    GLShader(GLuint object, GLenum type = GL_SHADER);

    ~GLShader();
  };
}// namespace Rendering
}// namespace Application