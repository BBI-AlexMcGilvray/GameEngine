#pragma once

#include "ShaderBase.h"

#include "Core/Headers/PtrDefs.h"

#include "Core/Math/Headers/Color.h"
#include "Core/Math/Headers/Vector4.h"
#include "Core/Math/Headers/Matrix4x4.h"

#include "Dependencies\Includes\GLEW\glew.h"

using namespace Core;
using namespace Core::Math;

namespace Application
{
	namespace Rendering
	{
		// holds onto vertex shader information
		struct DebugVertexShader : ShaderBase
		{
			DebugVertexShader()
				: ShaderBase("DebugVertexShader", GL_VERTEX_SHADER)
			{}

			Ptr<const char> GetShader() const override;

			virtual void Prepare(GLuint program, const Color& color);
			virtual void CleanUp();

		protected:
			static Ptr<const char> Shader;
		};
	}
}