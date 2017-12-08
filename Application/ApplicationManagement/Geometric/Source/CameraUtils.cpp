#include "ApplicationManagement/Geometric/Headers/CameraUtils.h"

#include "Core/Math/Headers/MathUtils.h"
#include "Core/Math/Headers/MatrixFunctions.h"

#include "Core/Debugging/Headers/Macros.h"

using namespace Core;

namespace Application
{
	namespace Geometric
	{
		Float4x4 CalculatePerspectiveMatrix(float fov, float aspectRatio, float nearPlane, float farPlane)
		{
			Float4x4 perspectiveMatrix;

			if (VERIFY(fov <= 0 || aspectRatio == 0))
			{
				return perspectiveMatrix;
			}

			float frustrumDepth = farPlane - nearPlane;
			float frustrumDepthInverse = 1.0f / frustrumDepth;

			perspectiveMatrix[0][0] = (1.0f / Tan(0.5f * fov)) / aspectRatio;
			perspectiveMatrix[1][1] = (1.0f / Tan(0.5f * fov));
			perspectiveMatrix[2][2] = farPlane * frustrumDepthInverse;
			perspectiveMatrix[2][3] = 1;
			perspectiveMatrix[3][2] = (-farPlane * nearPlane) * frustrumDepthInverse;
			perspectiveMatrix[3][3] = 0;

			return perspectiveMatrix;
		}
	}
}