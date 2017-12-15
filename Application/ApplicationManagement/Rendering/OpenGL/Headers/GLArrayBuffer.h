#pragma once

#include "GLObject.h"

namespace Application
{
	namespace Rendering
	{
		struct GLArrayBuffer : GLObject
		{
			GLArrayBuffer();
			GLArrayBuffer(GLuint object, GLenum type = GL_INVALID_ENUM);

			~GLArrayBuffer();

			void Bind();
			void Generate();
		};
	}
}