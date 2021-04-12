#include "ApplicationManagement/Animation/Headers/AnimationMixer.h"

#include "ApplicationManagement/Animation/Headers/Animatable.h"
#include "ApplicationManagement/Animation/Headers/Animation.h"

namespace Application
{
	namespace Animation
	{
		AnimationMixer::AnimationMixer(Core::Ptr<Animatable> target)
		{
			_target = target;
		}

		Core::Ptr<Animatable>& AnimationMixer::GetTarget()
		{
			return _target;
		}

		/*
		void AnimationMixer::MixValue(float weight, T value)
		{
			Core::Push(_valuesToMix, Core::Pair<float, T>(weight, value));
		}

		void AnimationMixer::Apply()
		{
			// does this need to be the initial value of the target instead? no, the animations should take it into account?
			T newValue;

			for (Core::Pair<float, T> pair : _valuesToMix)
			{
				newValue += pair.first * pair.second;
			}

			(*_target) = newValue;
		}
		*/
	}
}