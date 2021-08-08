#include "Pipeline/Rendering/OpenGL/Headers/GLObject.h"

namespace Application {
namespace Rendering {
  GLObject::GLObject()
    : Object(0), Type(GL_INVALID_ENUM)
  {}

  GLObject::GLObject(GLuint object, GLenum type)
    : Object(object), Type(type)
  {}

  void GLObject::SetObject(GLuint object)
  {
    Object = object;
  }

  void GLObject::SetType(GLenum type)
  {
    Type = type;
  }
}// namespace Rendering
}// namespace Application