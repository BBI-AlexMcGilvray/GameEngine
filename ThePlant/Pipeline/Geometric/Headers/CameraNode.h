#pragma once

#include "Pipeline/Geometric/Headers/Node.h"

#include "Pipeline/ECS/ObjectOriented/Headers/ComponentPtr.h"
#include "Pipeline/Rendering/Headers/RenderManager.h"

namespace Application {
namespace Geometric {
  // anything needed for camera. should create specifications for perspective and orthographic
  struct CameraNode : Node// inherits from node to have a transform, and to be able to be listed in the children of a scene (if needed?)
  {
    CameraNode(Core::Ptr<State> parentState, Ptr<Node> parentNode, Rendering::RenderManager &renderSystem, const float &aspectRatio);

    void Initialize() override;
    void Start() override;
  };
}// namespace Geometric
}// namespace Application