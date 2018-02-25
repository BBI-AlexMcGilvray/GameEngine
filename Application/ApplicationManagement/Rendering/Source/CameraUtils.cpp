#include "ApplicationManagement/Rendering/Headers/CameraUtils.h"

#include "Core/Math/Headers/MathUtils.h"
#include "Core/Math/Headers/MatrixFunctions.h"

#include "Core/Debugging/Headers/Macros.h"

using namespace Core;

namespace Application
{
	namespace Rendering
	{
		// this is wrong
		Float4x4 CalculatePerspectiveMatrix(float fovy, float aspectRatio, float nearPlane, float farPlane)
		{
			Float4x4 perspectiveMatrix;

			if (fovy <= 0 || aspectRatio == 0)
			{
				return perspectiveMatrix;
			}

			// Note: tan(FOV_H/2) / screen_width = tan(FOV_V/2) / screen_height

			float fovyRatio = Tan(0.5f * fovy);
			float fovxRatio = Tan(0.5f * fovyRatio * aspectRatio);
			float frustrumDepth = farPlane - nearPlane;
			float frustrumDepthInverse = 1.0f / frustrumDepth;

			perspectiveMatrix[0][0] = 1.0f / fovxRatio;
			perspectiveMatrix[1][1] = 1.0f / fovyRatio;
			perspectiveMatrix[2][2] = -(farPlane) * frustrumDepthInverse;
			perspectiveMatrix[2][3] = -1.0f;
			perspectiveMatrix[3][2] = -(farPlane * nearPlane) * frustrumDepthInverse;
			perspectiveMatrix[3][3] = 0;

			return perspectiveMatrix;
		}
	}
}