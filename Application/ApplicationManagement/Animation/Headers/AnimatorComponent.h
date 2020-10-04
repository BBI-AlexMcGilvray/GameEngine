#pragma once

#include "ApplicationManagement/Headers/Component.h"
#include "ApplicationManagement/Animation/Headers/AnimationManager.h"

namespace Application
{
	namespace Animation
	{
		struct IAnimator;

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

			Core::Ptr<IAnimator> AddAnimator(Core::UniquePtr<IAnimator> animator);

			Core::Ptr<IAnimator> AddAnimator(Core::Ptr<IAnimator> animator);

			void RemoveAnimator(Core::Ptr<IAnimator> animator);

		private:
			Core::Ptr<AnimationManager> _animationManager;
			Core::List<Core::Ptr<IAnimator>> _animators;
		};
	}
}