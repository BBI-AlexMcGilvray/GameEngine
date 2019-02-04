#include "ApplicationManagement/Geometric/Headers/CameraNode.h"

#include "ApplicationManagement/Geometric/Headers/ContentBase.h"

#include "ApplicationManagement/Rendering/Headers/CameraComponent.h"

namespace Application
{
	namespace Geometric
	{
		CameraNode::CameraNode(Ptr<State> parentState, Rendering::RenderManager& renderSystem, const float& aspectRatio)
			: Node(parentState)
		{
			CameraContent = AddContent(MakeUnique<ContentBase>());
			CameraContent->AddComponent<Rendering::CameraComponent>(renderSystem, aspectRatio);
		}
	}
}