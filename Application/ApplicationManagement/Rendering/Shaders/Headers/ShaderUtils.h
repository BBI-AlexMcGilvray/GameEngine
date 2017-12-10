#pragma once

#include "Dependencies\Includes\GLEW\glew.h"

#include "ObjectShaderBase.h"
#include "ShaderBase.h"

using namespace Core;

namespace Application
{
	namespace Rendering
	{
		void CreateProgram(Ptr<ObjectShaderBase> objectShader);
		GLuint CreateShader(Ptr<ShaderBase> shader);
	}
}