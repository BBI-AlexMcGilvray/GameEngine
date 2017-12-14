#pragma once

#include "Core/Headers/PtrDefs.h"

#include "ApplicationManagement/Rendering/OpenGL/Headers/GLObject.h"

using namespace Core;

namespace Application
{
	namespace Rendering
	{
		// holds onto vertex shader information
		struct ShaderBase : GLObject
		{
			const Ptr<const char> ShaderName;

			ShaderBase()
				: GLObject(0, GL_SHADER)
			{}

			ShaderBase(Ptr<const char> shaderName, GLenum shaderType)
				: GLObject(0, shaderType), ShaderName(shaderName)
			{}

			virtual ~ShaderBase() = default;

			virtual Ptr<const char> GetShader() const = 0;

			void SetShaderProgram(GLuint program)
			{
				Object = program;
			}

			GLenum GetShaderType() const
			{
				return Type;
			}
		};
	}
}