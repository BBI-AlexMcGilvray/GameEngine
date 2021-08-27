#pragma once

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/ListDefs.h"

#include "Pipeline/Rendering/OpenGL/Headers/GLArrayBuffer.h"
#include "Pipeline/Rendering/OpenGL/Headers/GLBuffer.h"

#include "Pipeline/Rendering/Shaders/Headers/ObjectShader.h"

#include "Pipeline/Rendering/Headers/RenderObjectBase.h"
#include "Pipeline/Rendering/3D/Headers/VertexData.h"

namespace Application {
namespace Rendering {
  // holds the information about the mesh of a 3D object
  struct CircleRenderObject : RenderObjectBase
  {
    GLArrayBuffer Vao;
    std::vector<GLBuffer> Vbos;

    CircleRenderObject(Core::Ptr<RenderManager> manager, Core::Ptr<Core::Geometric::Transform> renderTransform, Core::Math::Color color);
    CircleRenderObject(Core::Ptr<RenderManager> manager, Core::Ptr<Core::Geometric::Transform> renderTransform, Core::Math::Color color, float radius);

    ~CircleRenderObject();

    virtual void Initialize();

    virtual void Prepare(const Core::Math::Float4x4 &mvp, const Core::Math::Color &color) const;
    virtual void CleanUp() const;

    Core::size GetVertexCount() const override
    {
      return _vertices.size();
    }

  protected:
    ObjectShader &Shader;

    std::vector<SimpleVertexData> _vertices;
    float Radius;
  };
}// namespace Rendering
}// namespace Application