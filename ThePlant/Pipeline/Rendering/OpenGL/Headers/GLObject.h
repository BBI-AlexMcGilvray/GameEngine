#pragma once

#include "Dependencies/Includes/glew.h"

namespace Application {
namespace Rendering {
  struct GLObject
  {
    GLuint Object;
    GLenum Type;

    GLObject();
    GLObject(GLuint object, GLenum type);

    // if we treat any sub-objects as a GLObject, then this needs to be virtual!
    ~GLObject() = default;

    virtual void SetObject(GLuint object);
    virtual void SetType(GLenum type);

    bool operator==(const GLObject& other) const 
    {
      return (Object == other.Object && Type == other.Type);
    }
  };
}// namespace Rendering
}// namespace Application