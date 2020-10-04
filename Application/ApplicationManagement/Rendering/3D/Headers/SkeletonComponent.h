#pragma once

#include "ApplicationManagement/Headers/Component.h"

#include "ApplicationManagement/Rendering/Headers/RenderObjectManager.h"

namespace Application
{
	namespace Rendering
	{
		class AnimatedModel;
		class Skeleton;

		// a struct to hold all render objects of an entity
		struct SkeletonComponent : Component<SkeletonComponent>
		{
			static Core::Hash ClassHash()
			{
				return Core::HashValue("SkeletonComponent");
			}

			SkeletonComponent(Core::Ptr<EntityBase> entity, Core::Ptr<AnimatedModel> animatedModel);

			//template <typename ...Ts>
			//Core::Ptr<Skeleton> SetSkeleton(Ts&&... args)
			//{
			//	return SetSkeleton(Core::MakeUnique<Skeleton>(Forward<Ts>(args)...));
			//}

			//Core::Ptr<Skeleton> SetSkeleton(Core::UniquePtr<Skeleton> skeleton);
			//void RemoveSkeleton(Core::Ptr<Skeleton> skeleton);

		private:
			//Core::UniquePtr<Skeleton>
		};
	}
}