#pragma once

#include "Dependencies\Includes\GLEW\glew.h"

#include "ApplicationManagement/Rendering/Shaders/Headers/ObjectShaderBase.h"
#include "ApplicationManagement/Rendering/Shaders/Headers/ShaderBase.h"

using namespace Core;

namespace Application
{
	namespace Rendering
	{
		void CreateProgram(Ptr<ObjectShaderBase> objectShader);
		bool CreateShader(Ptr<ShaderBase> shader);
	}
}