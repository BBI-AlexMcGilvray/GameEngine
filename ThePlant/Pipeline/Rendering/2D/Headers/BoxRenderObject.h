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
  struct BoxRenderObject : RenderObjectBase
  {
    GLArrayBuffer Vao;
    std::vector<GLBuffer> Vbos;

    BoxRenderObject(Core::Ptr<RenderManager> manager, Core::Ptr<Core::Geometric::Transform> renderTransform, Core::Math::Color color);
    BoxRenderObject(Core::Ptr<RenderManager> manager, Core::Ptr<Core::Geometric::Transform> renderTransform, Core::Math::Color color, float width, float height);
    BoxRenderObject(Core::Ptr<RenderManager> manager, Core::Ptr<Core::Geometric::Transform> renderTransform, Core::Math::Color color, Core::Math::Float2 scale);

    ~BoxRenderObject();

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
    Float2 Scale;
  };
}// namespace Rendering
}// namespace Application