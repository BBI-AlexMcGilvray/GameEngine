#include "Pipeline/Rendering/Shaders/Headers/ObjectShaderBase.h"

#include "Pipeline/Rendering/OpenGL/Headers/ShaderUtils.h"

namespace Application {
namespace Rendering {
  ObjectShaderBase::ObjectShaderBase()
    : GLShaderProgram(0, GL_PROGRAM)
  {
  }

  ObjectShaderBase::~ObjectShaderBase()
  {
  }

  void ObjectShaderBase::Prepare(const Math::Float4x4 &mvp, const Math::Color &color) const
  {
    glUseProgram(Object);
  }

  void ObjectShaderBase::CleanUp() const
  {
    // default back to no shader
    glUseProgram(0);
  }


  void ObjectShaderBase::Initialize()
  {
    CreateProgram(this);
  }

  void ObjectShaderBase::Destroy()
  {
    glDeleteProgram(Object);
  }
}// namespace Rendering
}// namespace Application