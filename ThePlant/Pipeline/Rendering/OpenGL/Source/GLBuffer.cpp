#include "Pipeline/Rendering/OpenGL/Headers/GLBuffer.h"

#if _DEBUG
#include "Core/Debugging/Headers/Macros.h"
#endif
namespace Application {
namespace Rendering {
  GLBuffer::GLBuffer()
    : GLObject(0, GL_BUFFER)
  {}

  GLBuffer::GLBuffer(GLuint object, GLenum type)
    : GLObject(object, type)
  {}

  GLBuffer::~GLBuffer()
  {
    // don't delete here as any stack-based instances will clear for all and using pointers for this is probably unnecessary
  }

  void GLBuffer::Generate()
  {
    glGenBuffers(1, &Object);
  }

  void GLBuffer::Bind() const
  {
    glBindBuffer(Type, Object);
  }

  void GLBuffer::Unbind() const
  {
    glBindBuffer(Type, 0);
  }

  void GLBuffer::Delete()
  {
    glDeleteBuffers(1, &Object);
  }
}// namespace Rendering
}// namespace Application