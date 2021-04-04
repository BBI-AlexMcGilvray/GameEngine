#pragma once

#include "ApplicationManagement/Rendering/Headers/CameraManager.h"

namespace Application
{
	struct State;

	namespace Rendering
	{
		// this is how we should manage having different camera behavious (ex: simple camera manager that just maintains a single camera, or more complex behaviour like cinemachine)
		struct SingleCameraManager : public CameraManager
		{
			SingleCameraManager(Core::Ptr<RenderManager> manager);

			void Initialize() override;
			void Start() override;

			void Update(Core::Second dt) override;
			Core::Ptr<Camera> GetCamera() const override;

			void End() override;
			void CleanUp() override;

			Core::Ptr<Camera> AddCamera(Core::UniquePtr<Camera> camera) override;
			void RemoveCamera(Core::Ptr<Camera> camera) override;

		private:
			Core::UniquePtr<Camera> _camera = nullptr;
		};
	}
}
