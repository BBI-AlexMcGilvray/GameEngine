#include "ApplicationManagement/Geometric/Headers/World.h"

#include "ApplicationManagement/Geometric/Headers/CameraNode.h"

namespace Application
{
	namespace Geometric
	{
		World::World()
		{
			AddChild<CameraNode>(1024.0f / 800.0f);
		}
	}
}