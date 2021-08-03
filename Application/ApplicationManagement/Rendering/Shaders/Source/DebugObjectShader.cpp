#include "ApplicationManagement/Rendering/Shaders/Headers/DebugObjectShader.h"

namespace Application {
namespace Rendering {
  Ptr<const char> DebugObjectShader::Name = "ObjectShader";


  Ptr<const char> DebugObjectShader::GetName()
  {
    return Name;
  }

  Ptr<ShaderBase> DebugObjectShader::GetVertexShader()
  {
    return &FShader;
  }

  Ptr<ShaderBase> DebugObjectShader::GetFragmentxShader()
  {
    return &VShader;
  }

  void DebugObjectShader::Prepare(const Math::Float4x4 &mvp, const Math::Color &color) const
  {
    ObjectShaderBase::Prepare(mvp, color);

    VShader.Prepare(Object, color);
    FShader.Prepare();
  }

  void DebugObjectShader::CleanUp() const
  {
    VShader.CleanUp();
    FShader.CleanUp();

    ObjectShaderBase::CleanUp();
  }

  void DebugObjectShader::Initialize()
  {
    ObjectShaderBase::Initialize();

    glBindAttribLocation(Object, 0, "vPosition");// maybe not needed if specified in shader?
  }

  void DebugObjectShader::Destroy()
  {
    ObjectShaderBase::Destroy();
  }
}// namespace Rendering
}// namespace Application