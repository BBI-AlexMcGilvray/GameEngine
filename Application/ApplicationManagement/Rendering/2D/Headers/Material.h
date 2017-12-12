#pragma once

#include "Core/Headers/CoreDefs.h"
#include "Core/Math/Headers/Color.h"

using namespace Core;
using namespace Core::Math;

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