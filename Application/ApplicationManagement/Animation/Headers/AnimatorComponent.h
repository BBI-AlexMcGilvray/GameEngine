#pragma once

#include "ApplicationManagement/Headers/Component.h"
#include "ApplicationManagement/Animation/Headers/AnimationManager.h"

namespace Application
{
	namespace Animation
	{
		struct Animator;

		// a struct to hold all render objects of an entity
		struct AnimatorComponent : Component<AnimatorComponent>
		{
			static Core::Hash ClassHash()
			{
				return Core::HashValue("AnimatorComponent");
			}

			AnimatorComponent(Core::Ptr<EntityBase> entity, Core::Ptr<AnimationManager> animationManager);

			template <typename T, typename ...Ts>
			Core::Ptr<T> SetAnimator(Ts&& ...args)
			{
				return static_cast<Ptr<T>>(SetAnimator(Core::MakeUnique<T>(Forward<Ts>(args)...)));
			}

			Core::Ptr<Animator> SetAnimator(Core::UniquePtr<Animator> animator);

			void RemoveAnimator(Core::Ptr<Animator> animator);

		private:
			Core::Ptr<AnimationManager> _animationManager;
			Core::Ptr<Animator> _animator;
		};
	}
}