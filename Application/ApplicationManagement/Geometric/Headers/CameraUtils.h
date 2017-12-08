#pragma once

#include "Core/Math/Headers/Matrix4x4.h"

using namespace Core::Math;

namespace Application
{
	namespace Geometric
	{
		Float4x4 CalculatePerspectiveMatrix(float fov, float aspectRatio, float nearPlane, float farPlane);
	}
}