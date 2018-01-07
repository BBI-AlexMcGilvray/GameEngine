#include "ApplicationManagement/Geometric/Headers/CameraNode.h"

#include "ApplicationManagement/Rendering/Headers/CameraUtils.h"

#include "Core/Math/Headers/MathUtils.h"
#include "Core/Math/Headers/MatrixFunctions.h"
#include "Core/Math/Headers/VectorFunctions.h"
#include "Core/Math/Headers/QuaternionFunctions.h"

#include "Core/Debugging/Headers/Macros.h"

namespace Application
{
	namespace Geometric
	{
		CameraNode::CameraNode(const int& width, const int& height, const Float3& position, const Float3& direction)
			: RenderCamera(width, height, position, direction)
		{
		}

		void CameraNode::Update(Second dt)
		{
			Node::Update(dt);
		}

		void CameraNode::Render(Renderer& renderer, Float4x4 transformationMatrix)
		{
			// NOTE: the commented out code below should be done by the WORLD class

			// make this the currently used camera
			//auto previousCamera = renderer.GetCamera();
			//renderer.SetCamera(ToShared<Camera>(this));

			Node::Render(renderer, transformationMatrix);

			// switch back to previous camera
			//renderer.SetCamera(previousCamera);
		}
	}
}