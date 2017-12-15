#include "ApplicationManagement/Rendering/OpenGL/Headers/GLShaderProgram.h"

namespace Application
{
	namespace Rendering
	{
		GLShaderProgram::GLShaderProgram()
			: GLObject(0, GL_PROGRAM)
		{}

		GLShaderProgram::GLShaderProgram(GLuint object, GLenum type)
			: GLObject(object, type)
		{}

		GLShaderProgram::~GLShaderProgram()
		{
			// note: we are assuming that if a GLShaderProgram object exists in code, it has been initialized
			glDeleteProgram(Object);
		}
	}
}