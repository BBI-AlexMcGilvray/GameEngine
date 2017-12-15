#pragma once

#include "Core/Headers/PtrDefs.h"

#include "ApplicationManagement/Rendering/OpenGL/Headers/GLShader.h"

using namespace Core;

namespace Application
{
	namespace Rendering
	{
		// holds onto vertex shader information
		struct ShaderBase : GLShader
		{
			const Ptr<const char> ShaderName;

			ShaderBase(Ptr<const char> shaderName);
			ShaderBase(Ptr<const char> shaderName, GLenum shaderType);

			virtual ~ShaderBase() = default;

			virtual Ptr<const char> GetShader() const = 0;

			void SetShaderProgram(GLuint program);
		};
	}
}