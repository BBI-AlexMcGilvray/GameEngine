#include "ApplicationManagement/Rendering/Shaders/Headers/ObjectShaderBase.h"

#include "ApplicationManagement/Rendering/OpenGL/Headers/ShaderUtils.h"

namespace Application
{
	namespace Rendering
	{
		ObjectShaderBase::ObjectShaderBase()
			: GLShaderProgram(0, GL_PROGRAM)
		{
			Initialize();
		}

		ObjectShaderBase::~ObjectShaderBase()
		{
			Destroy();
		}

		void ObjectShaderBase::Prepare()
		{
			glUseProgram(Object);
		}

		void ObjectShaderBase::CleanUp()
		{

		}


		void ObjectShaderBase::Initialize()
		{
			CreateProgram(this);
		}

		void ObjectShaderBase::Destroy()
		{

		}
	}
}