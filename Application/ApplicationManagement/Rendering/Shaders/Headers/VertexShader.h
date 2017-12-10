#pragma once

#include "ShaderBase.h"

#include "Core/Headers/PtrDefs.h"

#include "Core/Math/Headers/Matrix4x4.h"

#include "ApplicationManagement\/Rendering\Headers\Color.h"

#include "Dependencies\Includes\GLEW\glew.h"

using namespace Core;

namespace Application
{
	namespace Rendering
	{
		// holds onto vertex shader information
		struct VertexShader : ShaderBase
		{
			VertexShader()
				: ShaderBase("VertexShader", GL_VERTEX_SHADER)
			{}

			Ptr<const char> GetShader() const override
			{
				return Shader;
			}

			virtual void Prepare(const Float4x4& mvp, const Color& color);
			virtual void CleanUp();

		protected:
			static Ptr<const char> Shader;
		};
	}
}