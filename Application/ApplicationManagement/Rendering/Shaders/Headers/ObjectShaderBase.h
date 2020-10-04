#pragma once

#include "ShaderBase.h"

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/ListDefs.h"
#include "Core/Math/Headers/Color.h"
#include "Core/Math/Headers/Matrix4x4.h"

#include "ApplicationManagement/Rendering/OpenGL/Headers/GLShaderProgram.h"

using namespace Core;

namespace Application
{
	namespace Rendering
	{
		// holds onto name (for reflection) and a pixel/vertex shader combination
		struct ObjectShaderBase : GLShaderProgram
		{
			ObjectShaderBase();
			virtual ~ObjectShaderBase();

			virtual Ptr<const char> GetName() = 0;

			virtual Ptr<ShaderBase> GetVertexShader() = 0;
			virtual Ptr<ShaderBase> GetFragmentxShader() = 0;

			virtual void Prepare(const Math::Float4x4& mvp, const Math::Color& color) const;
			virtual void CleanUp() const;

			void SetShaderProgram(GLuint program)
			{
				Object = program;
			}

			virtual void Initialize();
			virtual void Destroy();
		};
	}
}
