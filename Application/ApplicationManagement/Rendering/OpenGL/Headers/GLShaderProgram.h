#pragma once

#include "GLObject.h"

namespace Application
{
	namespace Rendering
	{
		struct GLShaderProgram : GLObject
		{
			GLShaderProgram();
			GLShaderProgram(GLuint object, GLenum type = GL_PROGRAM);

			~GLShaderProgram();
		};
	}
}