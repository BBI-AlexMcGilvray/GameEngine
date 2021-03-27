#include "ApplicationManagement/Rendering/Headers/CameraComponent.h"

#include "ApplicationManagement/Headers/Entity.h"

#include "Core/Debugging/Headers/Macros.h"

using namespace Core;

namespace Application
{
	namespace Rendering
	{
		CameraComponent::CameraComponent(Core::Ptr<EntityBase> entity, RenderManager& renderSystem, const float& aspectRatio)
			: Component<CameraComponent>(entity, this)
			, RenderSystem(renderSystem)
			, AspectRatio(aspectRatio)
		{

		}

		Core::Ptr<Camera> CameraComponent::GetCamera()
		{
			return RenderCamera.get();
		}

		void CameraComponent::Initialize()
		{
			Component<CameraComponent>::Initialize();

			ComponentPtr<Geometric::Hierarchy> hierarchyComponent = GetEntity()->GetComponent<Geometric::Hierarchy>();
			if (!VERIFY(hierarchyComponent))
			{
				return;
			}

			RenderCamera = move(MakeUnique<Camera>(AspectRatio, hierarchyComponent->GetHeirarchyNode()->Transformation));
			RenderSystem.SetCamera(GetCamera());
		}
	}
}