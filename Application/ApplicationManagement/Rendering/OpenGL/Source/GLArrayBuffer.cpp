#include "ApplicationManagement/Rendering/OpenGL/Headers/GLArrayBuffer.h"

namespace Application
{
	namespace Rendering
	{
		GLArrayBuffer::GLArrayBuffer()
			: GLObject(0, GL_INVALID_ENUM)
		{}

		GLArrayBuffer::GLArrayBuffer(GLuint object, GLenum type)
			: GLObject(object, type)
		{}

		void GLArrayBuffer::Bind()
		{
			glBindVertexArray(Object);
		}

		void GLArrayBuffer::Generate()
		{
			glGenVertexArrays(1, &Object);
		}
	}
}