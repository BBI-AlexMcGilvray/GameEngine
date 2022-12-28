#pragma once

#include "GLObject.h"

#include "Core/Math/Headers/Vector2.h"

namespace Application {
namespace Rendering {
  struct GLTexture : GLObject
  {
    GLTexture();
    GLTexture(GLuint object);

    ~GLTexture();

    void Generate();

    void Bind() const;

    // may need to support mip levels in the future
    void CreateTextureStorage(const Core::Math::Int2& dimensions, GLint format);
    void AttachToFrameBuffer(GLenum attachmentType);

    void Unbind() const;

    void Delete();
  };
}// namespace Rendering
}// namespace Application