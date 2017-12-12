#pragma once

#include "Core/Math/Headers/Color.h"

using namespace Core;
using namespace Core::Math;

namespace Data
{
	namespace Rendering
	{
		struct MaterialData
		{
			Color Specular;
			Color Diffuse;
			Color Ambient;
			float Shininess;

			MaterialData() = default;
			MaterialData(String fileName);
		};
	}
}