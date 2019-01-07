#include "ApplicationManagement\Rendering\Headers\RenderManager.h"

using namespace Core;
using namespace Core::Math;
using namespace Core::Functionality;

namespace Application
{
	namespace Rendering
	{
		RenderManager::RenderManager()
		{}

		void RenderManager::Initialize(WindowManager& window, Color clearColor)
		{
			ObjectShaderManager.Initialize();

			Window = &window;

			InitialColor = WHITE;
			ClearColor = clearColor;

			// don't render everything, but set up the default state
			RenderStart();
			RenderEnd();
		}

		void RenderManager::Start()
		{

		}

		void RenderManager::AttachRenderObjectManager(Ptr<RenderObjectManager> objectManager)
		{
			ObjectManager = objectManager;
		}

		void RenderManager::DettachRenderObjectManager(Ptr<RenderObjectManager> objectManager)
		{
			if (ObjectManager == objectManager)
			{
				ObjectManager = nullptr;
			}
		}

		void RenderManager::Update(Second dt)
		{
			// update render object manager
			if (ObjectManager != nullptr)
			{
				ObjectManager->Update(dt);
			}
			Render();
		}

		void RenderManager::Render()
		{
			RenderStart();
			RenderMiddle();
			RenderEnd();
		}

		void RenderManager::End()
		{

		}

		void RenderManager::CleanUp()
		{
			ObjectShaderManager.CleanUp();
		}

		void RenderManager::SetOpenGLAttributes()
		{
			// SDL_GL_CONTEXT_PROFILE_CORE uses only the newer version, deprecated functions are disabled
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

			// starting with version 3.2 of OpenGL as it is modern and should be runnable by most video cards
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

			// we are going to use double buffering (this only sets a 23bit Z buffer)
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

			// facing and culling
			glEnable(GL_CULL_FACE | GL_DEPTH_TEST);
			glFrontFace(GL_CW);
			glCullFace(GL_BACK);

			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // turns on wireframe mode
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // turns off wireframe mode
		}

		Ptr<const Camera> RenderManager::GetCamera() const
		{
			return RenderCamera;
		}

		void RenderManager::SetCamera(Ptr<Camera> renderCamera)
		{
			RenderCamera = renderCamera;
		}

		void RenderManager::RenderStart()
		{
			glClearColor(ClearColor.R, ClearColor.G, ClearColor.B, ClearColor.A);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// to render lines of triangles in mesh and both front and back
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		void RenderManager::RenderMiddle()
		{
			// NOTE: If rendering shadows and the like, we need to DISABLE culling of faces so that they are taken into account for shadows! (I think)
			
			// render manager render call
			auto initialMVP = RenderCamera->GetTransformationMatrix();
			if (ObjectManager != nullptr)
			{
				ObjectManager->Render(initialMVP, InitialColor);
			}
		}

		void RenderManager::RenderEnd()
		{
			SDL_GL_SwapWindow(Window->GetWindow());
		}
	}
}