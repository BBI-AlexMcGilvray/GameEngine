#include "ApplicationManagement/Rendering/Shaders/Headers/ObjectShaderBase.h"

#include "ApplicationManagement/Rendering/OpenGL/Headers/ShaderUtils.h"

namespace Application
{
	namespace Rendering
	{
		ObjectShaderBase::ObjectShaderBase()
			: GLObject(0, GL_PROGRAM)
		{
			Initialize();
		}

		ObjectShaderBase::~ObjectShaderBase()
		{
			Destroy();
		}

		void ObjectShaderBase::Initialize()
		{
			CreateProgram(this);
		}

		void ObjectShaderBase::Destroy()
		{
			// delete the shader program
			glDeleteProgram(Object);
		}
	}
}