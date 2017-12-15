#include "ApplicationManagement/Rendering/OpenGL/Headers/GLShader.h"

namespace Application
{
	namespace Rendering
	{
		GLShader::GLShader()
			: GLObject(0, GL_SHADER)
		{}

		GLShader::GLShader(GLuint object, GLenum type)
			: GLObject(object, type)
		{}
		
		GLShader::~GLShader()
		{
			// note: we are assuming that if a GLShader object exists in code, it has been initialized
			glDeleteShader(Object);
		}
	}
}