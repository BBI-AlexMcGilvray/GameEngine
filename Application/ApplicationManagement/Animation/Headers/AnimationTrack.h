#pragma once

#include "Core/Headers/ListDefs.h"
#include "Core/Headers/AnimationCurve.h"

namespace Application
{
	namespace Animation
	{
		template <typename T>
		class AnimationTrack
		{
		private:
			Core::AnimationCurve _curve;

		public:
			AnimationTrack();

			T Evaluate(Core::Second time);
		};
	}
}