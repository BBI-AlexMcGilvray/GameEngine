#include "ApplicationManagement\Rendering\Headers\RenderManager.h"

// dummy includes
#include "Core/Math/Headers/QuaternionFunctions.h"
#include "Core/Math/Headers/UtilityFunctions.h"

namespace Application
{
	namespace Rendering
	{
		RenderManager::RenderManager()
			: ObjectManager(this)
		{}

		void RenderManager::Initialize(WindowManager& window, Color clearColor)
		{
			ObjectShaderManager.Initialize();

			Window = &window;

			InitialColor = WHITE;
			ClearColor = clearColor;

			// don't render everything, but set up the default state
			SetCamera(MakeShared<Camera>(Window->Width, Window->Height));
			RenderStart();
			RenderEnd();
		}

		void RenderManager::Update(Second dt)
		{
			// update render object manager
			ObjectManager.Update(dt);
			Render(dt);
		}

		void RenderManager::Render(Second dt)
		{
			RenderStart();
			RenderMiddle(dt);
			RenderEnd();
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

		SharedPtr<const Camera> RenderManager::GetCamera() const
		{
			return RenderCamera;
		}

		void RenderManager::SetCamera(SharedPtr<Camera> renderCamera)
		{
			RenderCamera = renderCamera;
		}

		void RenderManager::RenderStart()
		{
			glClearColor(ClearColor.R, ClearColor.G, ClearColor.B, ClearColor.A);
			glClear(GL_COLOR_BUFFER_BIT);
		}

		void RenderManager::RenderMiddle(Second dt)
		{
			// render manager render call
			ObjectManager.Render(RenderCamera->GetRenderMatrix(), InitialColor);

			// dummy render
			float rotationSpeed = 0.5f;
			auto time = Duration(dt);
			for (auto& vertex : Vertices)
			{
				auto vertexMagnitude = Magnitude(vertex);
				auto newVertex = Core::Math::RotateNormalVectorBy(vertex, Core::Math::FQuaternion(0.707f, 0.0f, 0.0f, 0.707f));

				vertex = Normalize(Core::Math::Lerp(vertex, newVertex, rotationSpeed *time)) * vertexMagnitude;
			}

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

			Color dummyColor = BLUE;
			ObjectShaderManager.DebugShader.Prepare(dummyColor);
			Vao.Bind();
			// something is wrong with the buffers or the shaders
			ObjectRenderer.DrawLines(2);
			Vao.Unbind();
			ObjectShaderManager.DebugShader.CleanUp();
		}

		void RenderManager::RenderEnd()
		{
			SDL_GL_SwapWindow(Window->GetWindow());
		}
	}
}