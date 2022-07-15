#include "Pipeline/Rendering/OpenGL/Headers/GLMappedBuffer.h"

#include "Core/Logging/LogFunctions.h"

namespace Application {
namespace Rendering {
  GLMappedBuffer::GLMappedBuffer()
  {}

  GLMappedBuffer::GLMappedBuffer(GLuint object, GLenum type)
    : GLBuffer(object, type)
  {}

  GLMappedBuffer::~GLMappedBuffer()
  {
    // don't unmap here since map and unmap must be called together
  }

  void GLMappedBuffer::Map(GLenum accessType, bool internalHandling)
  {
    if (internalHandling) {
      Bind();
    }

    _mappedBuffer = glMapBuffer(Type, accessType);
    if (_mappedBuffer == nullptr) {
      DEBUG_LOG("GLMappedBuffer", "Failed to assign mapped buffer, glError: " + glGetError());
    }
  }

  void GLMappedBuffer::Assign(Core::Ptr<void> data, Core::size dataSize, bool internalHandling)
  {
    if (_mappedBuffer != nullptr) {
      memcpy(_mappedBuffer, data, dataSize);
    }
    else {
      DEBUG_LOG("GLMappedBuffer", "No buffer to assign to, glError: " + glGetError());
    }
  }

  bool GLMappedBuffer::Unmap(bool internalHandling) const
  {
    bool result = glUnmapBuffer(Type);

    if (internalHandling) {
      Unbind();
    }

    return result;
  }
}// namespace Rendering
}// namespace Application