#pragma once

#include "ApplicationManagement/Geometric/Headers/Node.h"

#include "ApplicationManagement/Rendering/Headers/CameraComponent.h"
#include "ApplicationManagement/Rendering/Headers/RenderManager.h"

namespace Application
{
	namespace Geometric
	{
		// anything needed for camera. should create specifications for perspective and orthographic
		struct CameraNode : Node // inherits from node to have a transform, and to be able to be listed in the children of a scene (if needed?)
		{
			ComponentPtr<Rendering::CameraComponent> CameraComponent;

			CameraNode(Core::Ptr<State> parentState, Ptr<Node> parentNode, Rendering::RenderManager& renderSystem, const float& aspectRatio);

			void Initialize() override;
			void Start() override;
		};
	}
}