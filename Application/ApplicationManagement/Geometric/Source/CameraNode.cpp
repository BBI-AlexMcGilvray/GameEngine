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
			Core::Ptr<ContentBase> cameraContent = AddContent(MakeUnique<ContentBase>(ParentState));
			CameraComponent = cameraContent->AddComponent<Rendering::CameraComponent>(renderSystem.GetCameraManagerForState(ParentState), aspectRatio);
		}

		void CameraNode::Initialize()
		{
			CameraComponent->Initialize();
		}

		void CameraNode::Start()
		{
			// this is not needed, only used at the moment to switch the circle colour from blue (default for node) to red
			// the debug content should be wrapped in a macro/script define so that it is always accessible anyways
			ContainerBase::Start();

			for (auto& child : Children)
			{
				child->Start();
			}

#if _DEBUG
			// debug
			Ptr<ContentBase> debugContent = AddContent<ContentBase>();

			ComponentPtr<Hierarchy> hierarchyComponent = debugContent->GetComponent<Hierarchy>();
			ComponentPtr<Rendering::Render> renderComponent = debugContent->AddComponent<Rendering::Render>(ApplicationManager::AppRenderManager().GetObjectManagerForState(ParentState));

			renderComponent->SetRenderObject<Rendering::CircleRenderObject>(&(hierarchyComponent->GetHeirarchyNode()->Transformation), RED, 0.25f);
#endif
		}
	}
}