#include "ApplicationManagement/Rendering/OpenGL/Headers/GLBuffer.h"

namespace Application
{
	namespace Rendering
	{
		GLBuffer::GLBuffer()
			: GLObject(0, GL_BUFFER)
		{}

		GLBuffer::GLBuffer(GLuint object, GLenum type)
			: GLObject(object, type)
		{}

		GLBuffer::~GLBuffer()
		{
			glDeleteBuffers(1, &Object);
		}

		void GLBuffer::Bind() const
		{
			glBindBuffer(Type, Object);
		}

		void GLBuffer::Generate()
		{
			glGenBuffers(1, &Object);
		}

		void GLBuffer::Unbind() const
		{
			glBindBuffer(Type, 0);
		}
	}
}