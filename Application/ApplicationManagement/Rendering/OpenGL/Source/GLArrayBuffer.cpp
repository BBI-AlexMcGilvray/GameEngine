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

		GLArrayBuffer::~GLArrayBuffer()
		{
			// don't delete here as any stack-based instances will clear for all and using pointers for this is probably unnecessary
		}

		void GLArrayBuffer::Generate()
		{
			glGenVertexArrays(1, &Object);
		}

		void GLArrayBuffer::Bind() const
		{
			glBindVertexArray(Object);
		}

		void GLArrayBuffer::Unbind() const
		{
			glBindVertexArray(0);
		}

		void GLArrayBuffer::Delete()
		{
			glDeleteVertexArrays(1, &Object);
		}
	}
}