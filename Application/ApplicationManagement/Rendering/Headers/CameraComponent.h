#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/Hash.h"

#include "ApplicationManagement/Headers/Component.h"

#include "ApplicationManagement/Geometric/Headers/HierarchyComponent.h"

#include "ApplicationManagement/Rendering/Headers/Camera.h"
#include "ApplicationManagement/Rendering/Headers/RenderManager.h"

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

			CameraComponent(Core::Ptr<EntityBase> entity, RenderManager& renderSystem, const float& aspectRatio = (1024.0f / 800.0f));

			Core::Ptr<Camera> GetCamera();

			void Initialize() override;

		private:
			RenderManager& RenderSystem;
			float AspectRatio;
			Core::UniquePtr<Camera> RenderCamera = nullptr;
		};
	}
}