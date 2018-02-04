#include "ApplicationManagement/Rendering/Shaders/Headers/ShaderManager.h"

namespace Application
{
	namespace Rendering
	{
		ShaderManager::ShaderManager()
		{

		}

		ShaderManager::~ShaderManager()
		{

		}

		Ptr<const ObjectShaderBase> ShaderManager::GetShader(ObjectShaderType shader) const
		{
			switch (shader)
			{
				case ObjectShaderType::Debug:
				{
					return &DebugShader;
				}
				case ObjectShaderType::Default:
				{
					return &DefaultShader;
				}
				default:
					return &DefaultShader;
			}
		}

		void ShaderManager::Initialize()
		{
			DebugShader.Initialize();
			DefaultShader.Initialize();
		}

		void ShaderManager::Destroy()
		{
			DebugShader.Destroy();
			DefaultShader.Destroy();
		}
	}
}