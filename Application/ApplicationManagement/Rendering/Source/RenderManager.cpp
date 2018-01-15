#include "ApplicationManagement\Rendering\Headers\RenderManager.h"

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
			ClearColor = clearColor;

			// create a dummy VAO/VBO and Shader pair to render
			{
				Vao.Generate();
				Vao.Bind();

				auto newBuffer = GLBuffer(0, GL_ARRAY_BUFFER);
				newBuffer.Generate();
				newBuffer.Bind();

				// glBufferData( < type >, < size of data >, < start of data >, < draw type >);
				glBufferData(newBuffer.Type, VertexCount * sizeof(Float3), &Vertices[0], GL_STATIC_DRAW);

				// glVertexAttribPointer(< vertex attrib array >, < number of ... >, < ... type of element >, < normalized? >, < new vertex every sizeof(<>) >, < offset of attribute >);
				// position
				glEnableVertexAttribArray(0); // this matches with object shader construction
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Float3), (void*)(0));

				Vao.Unbind();
				newBuffer.Unbind();
				glDisableVertexAttribArray(0);

				Push(Vbos, newBuffer);
			}

			// loop through once to start (this probably should not be done and should be replaced with loading screen or something)
			//Loop();
			LoopStart();
			LoopEnd();
		}

		void RenderManager::Update(Second dt)
		{
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
			ObjectShaderManager.Destroy();
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
		}

		void RenderManager::LoopStart()
		{
			glClearColor(ClearColor.R, ClearColor.G, ClearColor.B, ClearColor.A);
			glClear(GL_COLOR_BUFFER_BIT);
		}

		void RenderManager::LoopMiddle()
		{
			// render objects

			// dummy render
			Color dummyColor = Color(1.0f, 1.0f, 1.0f, 1.0f);
			ObjectShaderManager.DebugShader.Prepare(dummyColor);
			Vao.Bind();
			// something is wrong with the buffers or the shaders
			ObjectRenderer.DrawLines(2);
			Vao.Unbind();
			ObjectShaderManager.DebugShader.CleanUp();
		}

		void RenderManager::LoopEnd()
		{
			SDL_GL_SwapWindow(Window->GetWindow());
		}
	}
}