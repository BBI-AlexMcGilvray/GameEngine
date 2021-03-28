#include "ApplicationManagement/Rendering/Headers/CameraComponent.h"

#include "ApplicationManagement/Headers/Entity.h"

#include "Core/Debugging/Headers/Macros.h"

using namespace Core;

namespace Application
{
	namespace Rendering
	{
		CameraComponent::CameraComponent(Core::Ptr<EntityBase> entity, Core::Ptr<CameraManager> cameraManager, const float& aspectRatio)
			: Component<CameraComponent>(entity, this)
			, _cameraManager(cameraManager)
			, _aspectRatio(aspectRatio)
		{}

		Core::Ptr<Camera> CameraComponent::GetCamera()
		{
			return _camera;
		}

		void CameraComponent::Initialize()
		{
			Component<CameraComponent>::Initialize();

			ComponentPtr<Geometric::Hierarchy> hierarchyComponent = GetEntity()->GetComponent<Geometric::Hierarchy>();
			if (!VERIFY(hierarchyComponent))
			{
				return;
			}

			_camera = _cameraManager->AddCamera<Camera>(_aspectRatio, hierarchyComponent->GetHeirarchyNode()->Transformation);
		}
	}
}