#pragma once

#include "ApplicationManagement\Headers\GLContextManager.h"
#include "ApplicationManagement\Headers\WindowManager.h"

#include "ApplicationManagement/Rendering/Headers/RenderObjectManager.h"
#include "ApplicationManagement/Rendering/Headers/Renderer.h"
#include "ApplicationManagement/Rendering/Headers/Camera.h"
#include "ApplicationManagement/Rendering/Shaders/Headers/ShaderManager.h"

#include "Core/Functionality/Headers/Subscription.h"

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"
#include "Core/Headers/MapDefs.h"

#include "Core/Math/Headers/Vector4.h"
#include "Core/Math/Headers/Color.h"

namespace Application
{
	struct State;

	namespace Rendering
	{
		struct RenderManager
		{
			ShaderManager ObjectShaderManager;
			Renderer ObjectRenderer;

			// should subscribe to StateManager::StateChanged to change active state automatically
			RenderManager();

			void Initialize(WindowManager& window, Core::Math::Color clearColor = Core::Math::Color(1.0f, 0.5f, 0.5f, 1.0f));
			void Start();

			void AttachRenderObjectManager(Core::Ptr<State> state, Core::Ptr<RenderObjectManager> objectManager);
			void DettachRenderObjectManager(Core::Ptr<State> state);

			Core::Ptr<State> GetActiveState();
			void SetActiveState(Core::Ptr<State> state);
			void DeactivateState(Core::Ptr<State> state);
			Core::Ptr<RenderObjectManager> GetObjectManagerForState(Core::Ptr<State> state);

			void Update(Core::Second dt);
			void Render();

			void End();
			void CleanUp();

			void SetOpenGLAttributes();

			Core::Ptr<const Camera> GetCamera() const;
			void SetCamera(Core::Ptr<Camera> renderCamera);

		private:
			Core::Ptr<Camera> RenderCamera;
			Core::Math::Color InitialColor;

			Core::Math::Color ClearColor;
			Core::Ptr<WindowManager> Window;

			// maybe this should change to be a map of ptr to structs so that each renderobjectmanager can have a state, so that multiple can be active at once
			// this would allow transitioning to occur and such? unless our transitioning does not update the one being transitioned OUT of
			Core::Map<Core::Ptr<State>, Core::Ptr<RenderObjectManager>> ObjectManagers;
			Core::Ptr<State> ActiveState = nullptr;

			void RenderStart();
			void RenderMiddle();
			void RenderEnd();
		};
	}
}
