#pragma once

#include "ObjectShader.h"

namespace Application
{
	namespace Rendering
	{
		// holds list of ALL shaders that can be used, handles construction, retrieval and deletion of the shaders
		struct ShaderManager
		{
			ObjectShader DefaultShader;

			ShaderManager();
			~ShaderManager();

			void Initialize();
			void Destroy();
		};
	}
}