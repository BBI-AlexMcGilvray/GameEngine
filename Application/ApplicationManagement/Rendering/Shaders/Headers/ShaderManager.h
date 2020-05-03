#pragma once

#include "DebugObjectShader.h"
#include "ObjectShader.h"
#include "SkinnedObjectShader.h"

namespace Application
{
	namespace Rendering
	{
		// holds list of ALL shaders that can be used, handles construction, retrieval and deletion of the shaders
		struct ShaderManager
		{
			enum class ObjectShaderType
			{
				Debug,
				Default,
				SkinnedDefault
			};

			DebugObjectShader DebugShader;
			ObjectShader DefaultShader;
			SkinnedObjectShader DefaultSkinnedShader;

			ShaderManager();
			~ShaderManager();

			Ptr<const ObjectShaderBase> GetShader(ObjectShaderType shader) const;

			void Initialize();
			void CleanUp();
		};
	}
}