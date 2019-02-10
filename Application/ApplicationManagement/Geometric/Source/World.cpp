#include "ApplicationManagement/Geometric/Headers/World.h"

#include "ApplicationManagement/Headers/ApplicationManager.h"

#include "ApplicationManagement/Geometric/Headers/CameraNode.h"

#if _DEBUG
#include "ApplicationManagement/Geometric/Headers/ContentBase.h"
#include "ApplicationManagement/Geometric/Headers/HierarchyComponent.h"
#include "ApplicationManagement/Rendering/Headers/RenderComponent.h"
#include "ApplicationManagement/Rendering/2D/Headers/CircleRenderObject.h"
#endif

namespace Application
{
	namespace Geometric
	{
		World::World(Ptr<State> parentState)
			: Scene(parentState)
		{
			AddChild<Node>();

			Ptr<Node> cameraNode = AddChild<CameraNode>(ApplicationManager::AppRenderManager(), 1024.0f / 800.0f);
			cameraNode->Transformation.SetPosition(Float3(0.0f, 25.0f, 750.0f));
		}

		void World::Start()
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

			renderComponent->AddRenderObject<Rendering::CircleRenderObject>(&(hierarchyComponent->GetHeirarchyNode()->Transformation), BLACK, 0.25f);
#endif
		}
	}
}