#include "ApplicationManagement\Rendering\Headers\Renderer.h"

#include "ApplicationManagement/Rendering/Headers/RenderObjectBase.h"

namespace Application
{
	namespace Rendering
	{
		void Renderer::DrawMesh(Ptr<const RenderObjectBase> object) const
		{
			DrawLines(object->GetVertexCount());
		}

		void Renderer::Draw(Ptr<const RenderObjectBase> object) const
		{
			DrawTriangles(object->GetVertexCount());
		}

		void Renderer::DrawLines(uint vertexCount) const
		{
			glDrawArrays(GL_LINE_STRIP, 0, vertexCount);
		}

		void Renderer::DrawTriangles(uint vertexCount) const
		{
			glDrawArrays(GL_TRIANGLES, 0, vertexCount);
		}
	}
}