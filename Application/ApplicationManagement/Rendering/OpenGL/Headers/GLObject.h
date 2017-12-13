#pragma once

#include "Dependencies\Includes\GLEW\glew.h"

namespace Application
{
	namespace Rendering
	{
		struct GLObject
		{
			GLuint Object;
			GLenum Type;

			GLObject()
				: Object(0), Type(GL_INVALID_ENUM)
			{}

			GLObject(GLuint object, GLenum type)
				: Object(object), Type(type)
			{}
		};
	}
}