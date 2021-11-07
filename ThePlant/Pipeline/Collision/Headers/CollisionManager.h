#pragma once

#include <vector>

#include "ColliderBase.h"
#include "CollisionBase.h"

namespace Application {
namespace GameSystem {
  namespace Collision {
    struct CollisionManager
    {
      CollisionManager();

      void Initialize();
      void Start();

      void Update(Second dt);

      void End();
      void CleanUp();

    private:
      std::vector<ColliderBase> Colliders;
    };
  }// namespace Collision
}// namespace GameSystem
}// namespace Application