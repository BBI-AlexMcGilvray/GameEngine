#pragma once

#include "Pipeline\Collision\Headers\ColliderBase.h"

namespace Application {
namespace GameSystem {
  namespace Collision {
    struct CollisionBase
    {
      SharedPtr<const ColliderBase> C1;
      SharedPtr<const ColliderBase> C2;
      Float3 Location;

      CollisionBase(SharedPtr<const ColliderBase> c1, SharedPtr<const ColliderBase> c2, Float3 location);
    };
  }// namespace Collision
}// namespace GameSystem
}// namespace Application