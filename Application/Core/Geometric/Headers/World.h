#pragma once

#include "Core/Geometric/Headers/Scene.h"
#include "Core/Geometric/Headers/Camera.h"

namespace Core
{
	namespace Geometric
	{
		// a world is a scene, but it also has a camera (and probably more stuff in the future)
		struct World : Scene
		{
		protected:
			UniquePtr<Camera> WorldCamera;
		};
	}
}