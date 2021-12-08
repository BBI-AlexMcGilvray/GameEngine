#pragma once

#include "GLObject.h"
#include "GLBuffer.h"

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/CoreDefs.h"

namespace Application {
namespace Rendering {
  struct GLMappedBuffer : GLBuffer
  {
  private:
    Core::Ptr<void> _mappedBuffer = nullptr;

  public:
    GLMappedBuffer();
    GLMappedBuffer(GLuint object, GLenum type = GL_BUFFER);

    ~GLMappedBuffer();

    void Map(GLenum accessType, bool internalHandling = true);
    void Assign(Core::Ptr<void> data, Core::size dataSize, bool internalHandling = true);
    bool Unmap(bool internalHandling = true) const;

    bool operator==(const GLMappedBuffer& other) const
    {
      return (_mappedBuffer == other._mappedBuffer && GLBuffer::operator==(other));
    }
  };
}// namespace Rendering
}// namespace Application