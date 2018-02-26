#pragma once

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/PtrDefs.h"

#include "ApplicationManagement/Rendering/Headers/Camera.h"

using namespace Core;

namespace Application
{
	namespace Rendering
	{
		struct RenderObjectBase;

		// handles the actual rendering of any and all objects (probably should specialize for 2D and 3D objects)
		// this should also hold (a point perhaps) to the camera that is being used by the system
		struct Renderer
		{
			void DrawMesh(Ptr<const RenderObjectBase> object) const;
			void Draw(Ptr<const RenderObjectBase> object) const;

			void DrawLines(uint vertexCount) const;
			void DrawTriangles(uint vertexCount) const;
		};
	}
}