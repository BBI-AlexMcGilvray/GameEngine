#include "ApplicationManagement/Rendering/Shaders/Headers/ObjectShaderBase.h"

#include "ApplicationManagement/Rendering/Shaders/Headers/ShaderUtils.h"

namespace Application
{
	namespace Rendering
	{
		ObjectShaderBase::ObjectShaderBase()
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
			glDeleteProgram(Program);
		}
	}
}