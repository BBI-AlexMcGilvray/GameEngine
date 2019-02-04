#include "ApplicationManagement/Geometric/Headers/World.h"

#include "ApplicationManagement/Headers/ApplicationManager.h"

#include "ApplicationManagement/Geometric/Headers/CameraNode.h"

namespace Application
{
	namespace Geometric
	{
		World::World(Ptr<State> parentState)
			: Scene(parentState)
		{
			AddChild<Node>();

			Ptr<Node> cameraNode = AddChild<CameraNode>(ApplicationManager::AppRenderManager(), 1024.0f / 800.0f);
			cameraNode->Transformation.SetPosition(Float3(0.0f, 0.0f, 10.0f));
		}
	}
}