#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

#include "Core/Functionality/Headers/Event.h"
#include "Core/Geometric/Headers/Transform.h"

using namespace Core;
using namespace Core::Functionality;
using namespace Core::Geometric;

namespace Application {
namespace GameSystem {
  namespace Collision {
    struct CollisionBase;

    enum class ColliderType {
      Base,
      Box,
      Sphere
    };

    struct ColliderBase
    {
      /*
				This is an INTERFACE to be used by any object that needs collision.

				This template will handle holding onto collision information, subscribing to the collision manager to be rendered, and updating

				This template should be inherited from to produce specific collision requirements (ex: sphere vs box)

				Similar templates should be employed by Renderer and Game objects.

				So, for example, a game object with no collision information, we make a custom object that implements both GameObjectBase and RenderObjectBase (or children of) but NOT ColliderObjectBase
				*/

      // other collider that was hit, and where collision occured
      // NOTE: should pass collision, not each value
      Event<SharedPtr<const CollisionBase>> Collision;
      Event<SharedPtr<const CollisionBase>> Trigger;

      bool IsTrigger = false;

      virtual ColliderType GetColliderType() const
      {
        return ColliderType::Base;
      }

      const SharedPtr<const Transform> CollisionTransform;

      ColliderBase(SharedPtr<const Transform> collisionTransform);
      virtual ~ColliderBase();

      virtual void Update(Second dt);
      virtual void OnCollision(SharedPtr<const CollisionBase> collision);

      virtual float GetBoundingRadius() const = 0;
    };
  }// namespace Collision
}// namespace GameSystem
}// namespace Application