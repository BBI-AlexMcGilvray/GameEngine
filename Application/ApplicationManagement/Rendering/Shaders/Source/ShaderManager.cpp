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

		void ShaderManager::Initialize()
		{
			DefaultShader.Initialize();
		}

		void ShaderManager::Destroy()
		{
			DefaultShader.Destroy();
		}
	}
}