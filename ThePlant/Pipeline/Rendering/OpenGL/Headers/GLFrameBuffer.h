#pragma once

#include "GLObject.h"

namespace Application {
namespace Rendering {
  struct GLFrameBuffer : GLObject
  {
    GLFrameBuffer();
    GLFrameBuffer(GLuint object);

    ~GLFrameBuffer();

    void Generate();

    void Bind() const;

    void Unbind() const;

    void Delete();
  };
}// namespace Rendering
}// namespace Application