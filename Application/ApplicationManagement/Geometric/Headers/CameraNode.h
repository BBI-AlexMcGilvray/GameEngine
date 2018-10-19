#pragma once

#include "Core/Math/Headers/Vector2.h"

#include "ApplicationManagement/Geometric/Headers/Node.h"
#include "ApplicationManagement/Rendering/Headers/Camera.h"

namespace Application
{
	namespace Geometric
	{
		// anything needed for camera. should create specifications for perspective and orthographic
		struct CameraNode : Node // inherits from node to have a transform, and to be able to be listed in the children of a scene (if needed?)
		{
			Camera RenderCamera;

			CameraNode(const float& aspectRatio, const Float3& position = Float3(0.0f, 0.0f, 0.0f), const Float3& direction =Float3(0.0f, 0.0f, -1.0f));

			void Update(Second dt) override;
			void Render(Renderer& renderer, Float4x4 transformationMatrix) const override;
		};
	}
}