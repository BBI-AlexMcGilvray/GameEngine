#pragma once

#include "ColliderBase.h"
#include "CollisionBase.h"

#include "Core/Headers/ListDefs.h"

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
      List<ColliderBase> Colliders;
    };
  }// namespace Collision
}// namespace GameSystem
}// namespace Application