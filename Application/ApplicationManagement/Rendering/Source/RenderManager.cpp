#include "ApplicationManagement\Rendering\Headers\RenderManager.h"

namespace Application
{
	namespace Rendering
	{
		RenderManager::RenderManager()
		{}

		void RenderManager::Initialize(WindowManager& window, Math::Float4 clearColor)
		{
			Window = &window;
			ClearColor = clearColor;

			// loop through once to start (this probably should not be done and should be replaced with loading screen or something)
			Loop();
		}

		void RenderManager::Loop()
		{
			LoopStart();
			LoopMiddle();
			LoopEnd();
		}

		void RenderManager::CleanUp()
		{

		}

		void RenderManager::LoopStart()
		{
			glClearColor(ClearColor.X, ClearColor.Y, ClearColor.Z, ClearColor.W);
			glClear(GL_COLOR_BUFFER_BIT);
		}

		void RenderManager::LoopMiddle()
		{

		}

		void RenderManager::LoopEnd()
		{
			SDL_GL_SwapWindow(Window->GetWindow());
		}
	}
}