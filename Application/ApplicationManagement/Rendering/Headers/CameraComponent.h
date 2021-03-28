#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/Hash.h"

#include "ApplicationManagement/Headers/Component.h"

#include "ApplicationManagement/Geometric/Headers/HierarchyComponent.h"

#include "ApplicationManagement/Rendering/Headers/Camera.h"
#include "ApplicationManagement/Rendering/Headers/CameraManager.h"

namespace Application
{
	namespace Rendering
	{
		// a recursive struct to hold elements in a scene
		struct CameraComponent : Component<CameraComponent>
		{
			static Core::Hash ClassHash()
			{
				return Core::HashValue("Camera");
			}

			CameraComponent(Core::Ptr<EntityBase> entity, Core::Ptr<CameraManager> cameraManager, const float& aspectRatio = (1024.0f / 800.0f));

			Core::Ptr<Camera> GetCamera();

			void Initialize() override;

		private:
			Core::Ptr<CameraManager> _cameraManager;
			float _aspectRatio;
			Core::Ptr<Camera> _camera = nullptr;
		};
	}
}