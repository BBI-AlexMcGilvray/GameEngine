#pragma once

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/PtrDefs.h"

#include "ApplicationManagement/Geometric/Headers/Camera.h"

using namespace Core;
using namespace Application::Geometric;

namespace Application
{
	namespace Rendering
	{
		struct RenderObjectBase;

		// handles the actual rendering of any and all objects (probably should specialize for 2D and 3D objects)
		// this should also hold (a point perhaps) to the camera that is being used by the system
		struct Renderer
		{
			//SharedPtr<Camera> GetCamera();
			//void SetCamera(SharedPtr<Camera> renderCamera);

			void Draw(Ptr<RenderObjectBase> object);

		private:
			//SharedPtr<Camera> RenderCamera;

			void DrawLines(uint vertexCount);
			void DrawTriangles(uint vertexCount);
		};
	}
}