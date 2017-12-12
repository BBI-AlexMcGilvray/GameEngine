#pragma once

#include "Core/Headers/CoreDefs.h"
#include "Core/Math/Headers/Color.h"

#include "Data/Rendering/Headers/MaterialData.h"

using namespace Core;
using namespace Core::Math;

namespace Application
{
	namespace Rendering
	{
		// holds shader information in terms of how it is affected by light, shadows, ...
		struct Material : Data::Rendering::MaterialData
		{
			Material();
			Material(String fileName);
		};
	}
}