#pragma once

#include "ApplicationManagement/Rendering/Headers/Color.h"

#include "Core/Headers/CoreDefs.h"

namespace Application
{
	namespace Rendering
	{
		// holds shader information in terms of how it is affected by light, shadows, ...
		struct Material
		{
			Color Specular;
			Color Diffuse;
			Color Ambient;
			float Shininess;

			Material();
			Material(String fileName);
		};
	}
}