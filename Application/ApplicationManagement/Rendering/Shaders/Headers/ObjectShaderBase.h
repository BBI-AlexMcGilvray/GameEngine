#pragma once

#include "ShaderBase.h"

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/ListDefs.h"

#include "ApplicationManagement/Rendering/OpenGL/Headers/GLObject.h"

using namespace Core;

namespace Application
{
	namespace Rendering
	{
		// holds onto name (for reflection) and a pixel/vertex shader combination
		struct ObjectShaderBase : GLObject
		{
			ObjectShaderBase();
			virtual ~ObjectShaderBase();

			virtual Ptr<const char> GetName() = 0;

			virtual Ptr<ShaderBase> GetVertexShader() = 0;
			virtual Ptr<ShaderBase> GetFragmentxShader() = 0;

			virtual void Prepare();
			virtual void CleanUp();

			void SetShaderProgram(GLuint program)
			{
				Object = program;
			}

			virtual void Initialize();
			virtual void Destroy();
		};
	}
}
