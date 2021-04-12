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
			Core::Ptr<T> AddAnimator(Ts&& ...args)
			{
				return static_cast<Ptr<T>>(AddAnimator(_animatorManager->AddAnimator<T>(Forward<Ts>(args)...)));
			}

			Core::Ptr<Animator> AddAnimator(Core::UniquePtr<Animator> animator);

			Core::Ptr<Animator> AddAnimator(Core::Ptr<Animator> animator);

			void RemoveAnimator(Core::Ptr<Animator> animator);

		private:
			Core::Ptr<AnimationManager> _animationManager;
			Core::List<Core::Ptr<Animator>> _animators;
		};
	}
}