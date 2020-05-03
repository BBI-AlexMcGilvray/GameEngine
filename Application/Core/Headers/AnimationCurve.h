#pragma once

#include "ListDefs.h"
#include "Keyframe.h"

#include <tuple>

namespace Core
{
	struct AnimationCurve
	{
	public:
		AnimationCurve();
		AnimationCurve(List<Keyframe> keyframes);

		float Evaluate(Second time);

	private:
		List<Keyframe> _keyframes;

		std::tuple<Keyframe, Keyframe> GetClosestKeyframes(Second time);
	};
}