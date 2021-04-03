#pragma once

#include "ApplicationManagement/Headers/Component.h"

#include "ApplicationManagement/Geometric/Headers/Node.h"

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

			SkeletonComponent(Core::Ptr<EntityBase> entity);

			const Core::Ptr<Skeleton> GetSkeleton();

			template <typename T, typename ...Ts>
			Core::Ptr<T> SetSkeleton(Core::Ptr<State> parentState, Core::Ptr<Geometric::Node> parentNode, Ts&&... args)
			{
				Core::Ptr<Skeleton> newSkeleton = parentNode->AddChild<Skeleton>(Forward<Ts>(args)...);
				return SetSkeleton(newSkeleton);
			}

			Core::Ptr<Skeleton> SetSkeleton(Core::Ptr<Skeleton> skeleton);
			void RemoveSkeleton(Core::Ptr<Skeleton> skeleton);

		private:
			// skeletons are owned by the hierarchy
			Core::Ptr<Skeleton> _skeleton;
		};
	}
}