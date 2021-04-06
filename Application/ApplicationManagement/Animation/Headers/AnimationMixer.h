#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

namespace Application
{
	namespace Animation
	{
		// in the case of a skeleton, each bone is an animatable and they each get a mixer - do we want each animatable to have a mixer? it kind of makes sense...
		// this allows us to mix each one separately if the animations do not affect all bones
		template <typename T>
		class AnimationMixer
		{
		public:
			AnimationMixer() = default;

			AnimationMixer(Core::Ptr<T> target)
			{
				SetTarget(target);
			}

			void SetTarget(Core::Ptr<T> target)
			{
				_target = target;
			}

			Core::Ptr<T>& GetTarget()
			{
				return _target;
			}

			void MixValue(float weight, T value)
			{
				Core::Push(_valuesToMix, Core::Pair<float, T>(weight, value));
			}

			void Apply()
			{
				// does this need to be the initial value of the target instead? no, the animations should take it into account?
				T newValue;

				for (Core::Pair<float, T> pair : _valuesToMix)
				{
					newValue += pair.first * pair.second;
				}

				(*_target) = newValue;
			}

		private:
			Core::Ptr<T> _target;

			Core::List<Core::Pair<float, T>> _valuesToMix;
		};
	}
}