#pragma once

#include "Core/Headers/ListDefs.h"
#include "Core/Headers/TimeDefs.h"

#include "ApplicationManagement/Animation/Headers/Keyframe.h"

#include <tuple>

namespace Application
{
	namespace Animation
	{
		struct AnimationCurve
		{
		public:
			AnimationCurve();
			AnimationCurve(Core::List<Keyframe> keyframes);

			float Evaluate(Core::Second time);

		private:
			Core::List<Keyframe> _keyframes;

			std::tuple<Keyframe, Keyframe> GetClosestKeyframes(Core::Second time);
		};
	}
}