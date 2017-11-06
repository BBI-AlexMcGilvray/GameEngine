#pragma once

#include "ApplicationManagement\Headers\GLContextManager.h"
#include "ApplicationManagement\Headers\WindowManager.h"

#include "Core\Math\Headers\Vector4.h"

using namespace Core::Math;

namespace Application
{
	namespace Rendering
	{
		// handles the tie in between RenderObjectManager (object that needs to be rendered), ShaderManager (available shaders) and the Renderer (act of rendering them)
		struct RenderManager
		{
			RenderManager();

			void Initialize(WindowManager& window, Float4 clearColor = 0.0f);
			void Loop();
			void CleanUp();

			void SetOpenGLAttributes();

		private:
			Float4 ClearColor;
			WindowManager* Window;

			void LoopStart();
			void LoopMiddle();
			void LoopEnd();
		};
	}
}
