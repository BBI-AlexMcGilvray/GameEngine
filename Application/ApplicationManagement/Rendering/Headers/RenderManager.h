#pragma once

#include "ApplicationManagement\Headers\GLContextManager.h"
#include "ApplicationManagement\Headers\WindowManager.h"

#include "Renderer.h"
#include "ApplicationManagement/Rendering/Shaders/Headers/ShaderManager.h"

#include "Core/Functionality/Headers/Subscription.h"

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

#include "Core/Math/Headers/Vector4.h"
#include "Core/Math/Headers/Color.h"

// below is only used for the dummy data
#include "ApplicationManagement/Rendering/OpenGL/Headers/GLArrayBuffer.h"
#include "ApplicationManagement/Rendering/OpenGL/Headers/GLBuffer.h"
#include "ApplicationManagement/Rendering/Shaders/Headers/DebugObjectShader.h"

using namespace Core;
using namespace Core::Math;
using namespace Core::Functionality;

namespace Application
{
	namespace Rendering
	{
		// handles the tie in between RenderObjectManager (object that needs to be rendered), ShaderManager (available shaders) and the Renderer (act of rendering them)
		struct RenderManager // THIS SHOULD NOT INHERIT FROM SUBSCRIPTION - we need to handle the passing of the transformation matrix
			// perhaps the above is not so bad if the rendermanager (or maybe renderer?) has knowledge of the world so the transformation matrix can be passed down...
			// we SHOULD do the above, and modify Subscriber/Subscription to be TEMPLATED (so we know the types they are acting on/for) and then call an acceptable method.
		{
			ShaderManager ObjectShaderManager;
			Renderer ObjectRenderer;

			RenderManager();

			void Initialize(WindowManager& window, Color clearColor = Color(1.0f, 0.5f, 0.5f, 1.0f));
			void Update(Second dt);
			void Loop();
			void CleanUp();

			void SetOpenGLAttributes();

		private:
			Color ClearColor;
			Ptr<WindowManager> Window;

			void LoopStart();
			void LoopMiddle();
			void LoopEnd();

			// dummy garbage used to just test the shader system
			List<Float3> Vertices = { Float3(-1.0f, -1.0f, 0.0f), Float3(1.0f, 1.0f, 0.0f) };
			uint VertexCount = 2;

			GLArrayBuffer Vao;
			List<GLBuffer> Vbos;
		};
	}
}
