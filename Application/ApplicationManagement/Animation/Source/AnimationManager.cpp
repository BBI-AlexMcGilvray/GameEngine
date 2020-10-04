#include "ApplicationManagement/Animation/Headers/AnimationManager.h"

namespace Application
{
	namespace Animation
	{
		AnimationManager::AnimationManager()
		{}

		void AnimationManager::Initialize()
		{

		}

		void AnimationManager::Start()
		{

		}

		void AnimationManager::Update(Core::Second dt)
		{
			for (int i = 0; i < _animators.size(); i++)
			{
				_animators[i]->Update(dt);
			}
		}

		void AnimationManager::End()
		{

		}

		void AnimationManager::CleanUp()
		{

		}

		Core::Ptr<IAnimator> AnimationManager::AddAnimator(Core::UniquePtr<IAnimator> animator)
		{
			Core::Push(_animators, move(animator));

			return _animators[_animators.size() - 1].get();
		}

		void AnimationManager::RemoveAnimator(Core::Ptr<IAnimator> animator)
		{
			for (Core::size i = 0; i < _animators.size(); i++)
			{
				if (_animators[i].get() == animator)
				{
					Core::RemoveIndex(_animators, i);
				}
			}
		}
	}
}