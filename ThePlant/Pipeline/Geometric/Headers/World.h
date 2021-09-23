#pragma once

#include "Pipeline/Geometric/Headers/Scene.h"

namespace Application {
namespace Geometric {
  // a world is a scene, but it also has a camera (by default?) (and probably more stuff in the future)
  struct World : Scene
  {
    World(Core::Ptr<State> parentState);

    void Initialize() override;
    void Start() override;
  };
}// namespace Geometric
}// namespace Application