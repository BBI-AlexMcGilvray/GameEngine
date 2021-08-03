#include "ApplicationManagement\Rendering\Headers\Renderer.h"

#include "ApplicationManagement/Rendering/Headers/RenderObjectBase.h"

#include "Dependencies/Includes/glew.h"

using namespace Core;

namespace Application {
namespace Rendering {
  void Renderer::DrawMesh(Ptr<const RenderObjectBase> object) const
  {
    DrawLines(object->GetVertexCount());
  }

  void Renderer::Draw(Ptr<const RenderObjectBase> object) const
  {
    DrawTriangles(object->GetVertexCount());
  }

  void Renderer::DrawLines(Core::size vertexCount) const
  {
    VERIFY((INT32_MAX >= vertexCount));
    glDrawArrays(GL_LINE_STRIP, 0, GLsizei(vertexCount));
  }

  void Renderer::DrawTriangles(Core::size vertexCount) const
  {
    VERIFY((INT32_MAX >= vertexCount));
    glDrawArrays(GL_TRIANGLES, 0, GLsizei(vertexCount));
  }
}// namespace Rendering
}// namespace Application