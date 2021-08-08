#include "Pipeline/Collision/Headers/CollisionBase.h"

namespace Application {
namespace GameSystem {
  namespace Collision {
    CollisionBase::CollisionBase(SharedPtr<const ColliderBase> c1, SharedPtr<const ColliderBase> c2, Float3 location)
      : C1(c1), C2(c2), Location(location)
    {}
  }// namespace Collision
}// namespace GameSystem
}// namespace Application