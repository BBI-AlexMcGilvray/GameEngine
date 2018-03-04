#pragma once

#include "Core/Math/Headers/Matrix4x4.h"

using namespace Core::Math;

namespace Application
{
	namespace Rendering
	{
		Float4x4 CalculatePerspectiveMatrix(Rad fov, float aspectRatio, float nearPlane, float farPlane);
	}
}