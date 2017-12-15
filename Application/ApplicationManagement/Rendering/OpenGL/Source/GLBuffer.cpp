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

		void GLBuffer::Bind()
		{
			Bind(Type);
		}

		void GLBuffer::Bind(GLenum type)
		{
			Type = type;
			glBindBuffer(type, Object);
		}

		void GLBuffer::Generate()
		{
			glGenBuffers(1, &Object);
		}
	}
}