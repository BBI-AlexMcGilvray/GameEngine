#include "ApplicationManagement/Geometric/Headers/CameraNode.h"

#include "ApplicationManagement/Geometric/Headers/ContentBase.h"

#if _DEBUG
#include "ApplicationManagement/Headers/ApplicationManager.h"
#include "ApplicationManagement/Rendering/Headers/RenderComponent.h"
#include "ApplicationManagement/Rendering/2D/Headers/CircleRenderObject.h"
#endif

namespace Application
{
	namespace Geometric
	{
		CameraNode::CameraNode(Ptr<State> parentState, Ptr<Node> parentNode, Rendering::RenderManager& renderSystem, const float& aspectRatio)
			: Node(parentState, parentNode)
		{
			Core::Ptr<ContentBase> cameraContent = AddContent(MakeUnique<ContentBase>());
			CameraComponent = cameraContent->AddComponent<Rendering::CameraComponent>(renderSystem, aspectRatio);
		}

		void CameraNode::Start()
		{
			ContainerBase::Start();

			for (auto& child : Children)
			{
				child->Start();
			}

#if _DEBUG
			// debug
			Ptr<ContentBase> debugContent = AddContent(MakeUnique<ContentBase>());

			ComponentPtr<Hierarchy> hierarchyComponent = debugContent->GetComponent<Hierarchy>();
			ComponentPtr<Rendering::Render> renderComponent = debugContent->AddComponent<Rendering::Render>(ApplicationManager::AppRenderManager().GetObjectManagerForState(ParentState));

			renderComponent->AddRenderObject<Rendering::CircleRenderObject>(&(hierarchyComponent->GetHeirarchyNode()->Transformation), RED, 0.25f);
#endif
		}
	}
}