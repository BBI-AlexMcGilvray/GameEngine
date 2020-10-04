#pragma once

#include "Core/Headers/ListDefs.h"
#include "Core/Headers/TimeDefs.h"

#include "ApplicationManagement/Animation/Headers/Animator.h"

namespace Application
{
	namespace Animation
	{
		class AnimationManager
		{
			// Need a way to handle animators no longer being relevant for the current state
		public:
			AnimationManager();

			void Initialize();
			void Start();

			void Update(Core::Second dt);

			void End();
			void CleanUp();

			template <typename T, typename ...Ts>
			Core::Ptr<T> AddAnimator(Ts&& ...args)
			{
				Core::UniquePtr<IAnimator> newAnimator = Core::MakeUnique<T>(Forward<Ts>(args)...);

				return static_cast<Ptr<T>>(AddAnimator(move(newAnimator)));
			}

			Core::Ptr<IAnimator> AddAnimator(Core::UniquePtr<IAnimator> animator);
			void RemoveAnimator(Core::Ptr<IAnimator> animator);

		private:
			// Should this not be ptrs at all to have contiguous memory?
			// ~ that would mean they would need to live here, and not on a component
			// ~ so components point to element held by array within the system instead of the other way around
			Core::List<Core::UniquePtr<IAnimator>> _animators;
		};
	}
}