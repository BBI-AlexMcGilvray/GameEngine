#pragma once

#include "ApplicationManagement\Headers\GLContextManager.h"
#include "ApplicationManagement\Headers\WindowManager.h"

#include "Renderer.h"
#include "ApplicationManagement/Rendering/Shaders/Headers/ShaderManager.h"

#include "Core/Functionality/Headers/Subscription.h"

#include "Core/Headers/PtrDefs.h"
#include "Core/Math/Headers/Vector4.h"
#include "Core/Math/Headers/Color.h"

using namespace Core;
using namespace Core::Math;
using namespace Core::Functionality;

namespace Application
{
	namespace Rendering
	{
		// handles the tie in between RenderObjectManager (object that needs to be rendered), ShaderManager (available shaders) and the Renderer (act of rendering them)
		struct RenderManager : Subscription // THIS SHOULD NOT INHERIT FROM SUBSCRIPTION - we need to handle the passing of the transformation matrix
		{
			ShaderManager ObjectShaderManager;
			Renderer ObjectRenderer;

			RenderManager();

			void Initialize(WindowManager& window, Color clearColor = Color(0.5f, 0.5f, 0.5f, 1.0f));
			void Loop();
			void CleanUp();

			void SetOpenGLAttributes();

		private:
			Color ClearColor;
			Ptr<WindowManager> Window;

			void LoopStart();
			void LoopMiddle();
			void LoopEnd();
		};
	}
}
