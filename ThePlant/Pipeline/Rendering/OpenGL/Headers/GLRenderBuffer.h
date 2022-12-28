#pragma once

#include "GLObject.h"

#include "Core/Math/Headers/Vector2.h"

namespace Application {
namespace Rendering {
  struct GLRenderBuffer : GLObject
  {
    GLRenderBuffer();
    GLRenderBuffer(GLuint object);

    ~GLRenderBuffer();

    void Generate();

    void Bind() const;

    void CreateBufferStorage(const Core::Math::Int2& dimensions, GLenum format);
    void AttachToFrameBuffer(GLenum attachmentType);

    void Unbind() const;

    void Delete();
  };
}// namespace Rendering
}// namespace Application