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

#include "Core/Math/Headers/Vector4.h"
#include "Core/Math/Headers/Color.h"

namespace Application
{
	namespace Rendering
	{
		// handles the tie in between RenderObjectManager (object that needs to be rendered), ShaderManager (available shaders) and the Renderer (act of rendering them)
		struct RenderManager
		{
			ShaderManager ObjectShaderManager;
			Renderer ObjectRenderer;
			Core::Ptr<RenderObjectManager> ObjectManager = nullptr;

			RenderManager();

			void Initialize(WindowManager& window, Core::Math::Color clearColor = Core::Math::Color(1.0f, 0.5f, 0.5f, 1.0f));
			void Start();

			void AttachRenderObjectManager(Core::Ptr<RenderObjectManager> objectManager);
			void DettachRenderObjectManager(Core::Ptr<RenderObjectManager> objectManager);

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

			void RenderStart();
			void RenderMiddle();
			void RenderEnd();
		};
	}
}
