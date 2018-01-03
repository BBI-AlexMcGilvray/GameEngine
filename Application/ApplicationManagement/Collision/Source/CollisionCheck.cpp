#include "ApplicationManagement/Collision/Headers/CollisionCheck.h"

using namespace std;

namespace Application
{
	namespace GameSystem
	{
		namespace Collision
		{
			// Collisions
			UniquePtr<CollisionBase> Collide(SharedPtr<const ColliderBase> c1, SharedPtr<const ColliderBase> c2)
			{
				if (!QuickCheckCollision(c1, c2))
				{
					return nullptr;
				}

				switch (c1->GetColliderType())
				{
					case ColliderType::Box:
					{
						switch (c2->GetColliderType())
						{
							case ColliderType::Box:
							{
								return Collide(static_pointer_cast<const BoxCollider>(c1), static_pointer_cast<const BoxCollider>(c2));
							}
							case ColliderType::Sphere:
							{
								return Collide(static_pointer_cast<const BoxCollider>(c1), static_pointer_cast<const SphericalCollider>(c2));
							}
							case ColliderType::Base:
							{
								// not possible...
								break;
							}
						}
					}
					case ColliderType::Sphere:
					{
						switch (c2->GetColliderType())
						{
							case ColliderType::Box:
							{
								return Collide(static_pointer_cast<const SphericalCollider>(c1), static_pointer_cast<const BoxCollider>(c2));
							}
							case ColliderType::Sphere:
							{
								return Collide(static_pointer_cast<const SphericalCollider>(c1), static_pointer_cast<const SphericalCollider>(c2));
							}
							case ColliderType::Base:
							{
								// not possible...
								break;
							}
						}
					}
					case ColliderType::Base:
					{
						// not possible...
						break;
					}
				}

				return nullptr;
			}

			// Box
			UniquePtr<CollisionBase> Collide(SharedPtr<const BoxCollider> box1, SharedPtr<const BoxCollider> box2)
			{
				if (CheckCollision(box1, box2))
				{
					return MakeUnique<CollisionBase>(box1, box2, GetCollisionLocation(box1, box2));
				}

				return nullptr;
			}

			UniquePtr<CollisionBase> Collide(SharedPtr<const BoxCollider> box, SharedPtr<const SphericalCollider> sphere)
			{
				if (CheckCollision(box, sphere))
				{
					return MakeUnique<CollisionBase>(box, sphere, GetCollisionLocation(box, sphere));
				}

				return nullptr;
			}

			// Sphere
			UniquePtr<CollisionBase> Collide(SharedPtr<const SphericalCollider> sphere1, SharedPtr<const SphericalCollider> sphere2)
			{
				if (CheckCollision(sphere1, sphere2))
				{
					return MakeUnique<CollisionBase>(sphere1, sphere2, GetCollisionLocation(sphere1, sphere2));
				}

				return nullptr;
			}

			UniquePtr<CollisionBase> Collide(SharedPtr<const SphericalCollider> sphere, SharedPtr<const BoxCollider> box)
			{
				return Collide(box, sphere);
			}

			// general collision checks
			bool QuickCheckCollision(SharedPtr<const ColliderBase> c1, SharedPtr<const ColliderBase> c2)
			{
				float colliderDistance = Distance(c1->CollisionTransform->Position, c2->CollisionTransform->Position);
				float maxReach = (c1->GetBoundingRadius() + c2->GetBoundingRadius());

				return (colliderDistance < maxReach);
			}

			// specific collision checks
			bool CheckCollision(SharedPtr<const BoxCollider> box1, SharedPtr<const BoxCollider> box2)
			{
				// not done yet, need to have box colliders build from planes first
				return false;

				// once planes are implemented... (including rotation)
				/*
				Cast ray from box1 to box2
				Find two planes that get hit by ray (one from box1, one from box2)
				For each plane:
					For each edge of the relevant plane:
						Cast ray, determine if it intersects other plane
						If it does, true
						Else, continue
				false
				*/
			}

			bool CheckCollision(SharedPtr<const BoxCollider> box, SharedPtr<const SphericalCollider> sphere)
			{
				// not done yet, need to have box colliders build from planes first
				return false;

				// once planes are implemented... (including rotation)
				/*
				Cast ray from box to sphere center
				Find plane that ray intersects
				Determine distance from sphere to point of intersection from ray and plane
				If distance is less than sphere radius - collision
				*/
			}

			bool CheckCollision(SharedPtr<const SphericalCollider> sphere1, SharedPtr<const SphericalCollider> sphere2)
			{
				// this is just a duplicate of the quick check, so no need to do the calculation (unless the quick check changes later)
				/*
				float colliderDistance = Distance(sphere1->CollisionTransform->Position, sphere2->CollisionTransform->Position);
				float maxReach = (sphere1->GetBoundingRadius() + sphere2->GetBoundingRadius());

				return (colliderDistance < maxReach);
				*/
				return true;
			}

			// get collision locations
			Float3 GetCollisionLocation(SharedPtr<const BoxCollider> box1, SharedPtr<const BoxCollider> box2)
			{
				// not done yet, need to have box colliders build from planes first
				return Float3(0.0f);

				// once planes are implemented... (including rotation)
				/*
				Cast ray from box1 to box2
				Find two planes that get hit by ray (one from box1, one from box2)
				For each plane:
					For each edge of the relevant plane:
						Cast ray, determine if it intersects other plane
						If it does, store position
						Else, continue
				
				retrun average of positions
				*/
			}

			Float3 GetCollisionLocation(SharedPtr<const BoxCollider> box, SharedPtr<const SphericalCollider> sphere)
			{
				// not done yet, need to have box colliders build from planes first
				return Float3(0.0f);

				// once planes are implemented... (including rotation)
				/*
				Cast ray from box to sphere center
				Find plane that ray intersects, store position of intersection
				Find furthest point of sphere in plane, store position
				
				return average of positions
				*/
			}

			Float3 GetCollisionLocation(SharedPtr<const SphericalCollider> sphere1, SharedPtr<const SphericalCollider> sphere2)
			{
				Float3 direction = (sphere1->CollisionTransform->Position - sphere2->CollisionTransform->Position);
				Float3 middlePoint = sphere1->CollisionTransform->Position + (direction / 2.0f);
				
				return (middlePoint);
			}
		}
	}
}