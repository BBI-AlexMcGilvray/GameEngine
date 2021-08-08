#pragma once

#include "ColliderBase.h"
#include "BoxCollider.h"
#include "SphericalCollider.h"

#include "CollisionBase.h"

namespace Application {
namespace GameSystem {
  namespace Collision {
    // Collisions
    UniquePtr<CollisionBase> Collide(SharedPtr<const ColliderBase> c1, SharedPtr<const ColliderBase> c2);
    // Box
    UniquePtr<CollisionBase> Collide(SharedPtr<const BoxCollider> box1, SharedPtr<const BoxCollider> box2);
    UniquePtr<CollisionBase> Collide(SharedPtr<const BoxCollider> box, SharedPtr<const SphericalCollider> sphere);
    // Sphere
    UniquePtr<CollisionBase> Collide(SharedPtr<const SphericalCollider> sphere1, SharedPtr<const SphericalCollider> sphere2);
    UniquePtr<CollisionBase> Collide(SharedPtr<const SphericalCollider> sphere, SharedPtr<const BoxCollider> box);

    // general collision checks
    bool QuickCheckCollision(SharedPtr<const ColliderBase> c1, SharedPtr<const ColliderBase> c2);

    // specific collision checks
    bool CheckCollision(SharedPtr<const BoxCollider> box1, SharedPtr<const BoxCollider> box2);
    bool CheckCollision(SharedPtr<const BoxCollider> box, SharedPtr<const SphericalCollider> sphere);
    bool CheckCollision(SharedPtr<const SphericalCollider> sphere1, SharedPtr<const SphericalCollider> sphere2);

    // get collision locations
    Float3 GetCollisionLocation(SharedPtr<const BoxCollider> box1, SharedPtr<const BoxCollider> box2);
    Float3 GetCollisionLocation(SharedPtr<const BoxCollider> box, SharedPtr<const SphericalCollider> sphere);
    Float3 GetCollisionLocation(SharedPtr<const SphericalCollider> sphere1, SharedPtr<const SphericalCollider> sphere2);
  }// namespace Collision
}// namespace GameSystem
}// namespace Application