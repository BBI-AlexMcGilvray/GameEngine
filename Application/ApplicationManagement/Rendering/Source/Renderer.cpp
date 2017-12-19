#include "ApplicationManagement\Rendering\Headers\Renderer.h"

#include "ApplicationManagement/Rendering/Headers/RenderObjectBase.h"

namespace Application
{
	namespace Rendering
	{
		/*
		SharedPtr<Camera> Renderer::GetCamera()
		{
			return RenderCamera;
		}

		void Renderer::SetCamera(SharedPtr<Camera> renderCamera)
		{
			RenderCamera = renderCamera;
		}
		*/
		void Renderer::Draw(Ptr<RenderObjectBase> object)
		{
			DrawTriangles(object->GetVertexCount());
		}

		void Renderer::DrawLines(uint vertexCount)
		{
			glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
		}

		void Renderer::DrawTriangles(uint vertexCount)
		{
			glDrawArrays(GL_TRIANGLES, 0, vertexCount);
		}
	}
}