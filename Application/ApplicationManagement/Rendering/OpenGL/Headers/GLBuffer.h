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

			void Generate();

			void Bind() const;

			void Unbind() const;

			void Delete();
		};
	}
}