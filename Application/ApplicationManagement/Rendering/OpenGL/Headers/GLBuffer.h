#pragma once

#include "GLObject.h"

namespace Application
{
	namespace Rendering
	{
		struct GLBuffer : GLObject
		{
			GLBuffer();
			GLBuffer(GLuint object, GLenum type = GL_BUFFER);

			~GLBuffer();

			void Bind() const;

			void Generate();

			void Unbind() const;
		};
	}
}