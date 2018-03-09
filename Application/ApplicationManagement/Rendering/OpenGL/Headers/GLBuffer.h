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

			virtual void Bind() const;

			virtual void Generate();

			virtual void Unbind() const;
		};
	}
}