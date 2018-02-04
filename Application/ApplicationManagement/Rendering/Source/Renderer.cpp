#include "ApplicationManagement\Rendering\Headers\Renderer.h"

#include "ApplicationManagement/Rendering/Headers/RenderObjectBase.h"

namespace Application
{
	namespace Rendering
	{
		SharedPtr<const Camera> Renderer::GetCamera() const
		{
			return RenderCamera;
		}

		void Renderer::SetCamera(SharedPtr<Camera> renderCamera)
		{
			RenderCamera = renderCamera;
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