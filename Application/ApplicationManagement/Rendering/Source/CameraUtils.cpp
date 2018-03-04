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
		Float4x4 CalculatePerspectiveMatrix(Rad fovy, float aspectRatio, float nearPlane, float farPlane)
		{
			Float4x4 perspectiveMatrix;

			if (fovy <= 0 || aspectRatio == 0)
			{
				return perspectiveMatrix;
			}

			// Note: tan(FOV_H/2) / screen_width = tan(FOV_V/2) / screen_height

			float fovyRatio = 1.0f / Tan(0.5f * fovy);
			float fovxRatio = fovyRatio / aspectRatio;
			float frustrumDepth = farPlane - nearPlane;

			perspectiveMatrix[0][0] = fovxRatio;
			perspectiveMatrix[1][1] = fovyRatio;
			perspectiveMatrix[2][2] = -1.0f * (farPlane + nearPlane) / frustrumDepth;
			perspectiveMatrix[2][3] = -1.0f;
			perspectiveMatrix[3][2] = -2.0f * (farPlane * nearPlane) / frustrumDepth;
			perspectiveMatrix[3][3] = 0.0f;

			return perspectiveMatrix;
		}
	}
}