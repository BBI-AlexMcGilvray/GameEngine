#include "Core/Headers/AnimationCurve.h"

#include "Core/Debugging/Headers/Macros.h"

namespace Core
{
	AnimationCurve::AnimationCurve()
		: AnimationCurve({ Keyframe(0_s, 0.0f), Keyframe(1_s, 0.0f) })
	{}

	AnimationCurve::AnimationCurve(List<Keyframe> keyframes)
		: _keyframes(keyframes)
	{}

	// Source: https://forum.unity.com/threads/need-way-to-evaluate-animationcurve-in-the-job.532149/
	float AnimationCurve::Evaluate(Second time)
	{
		float t = Duration(time);

		std::tuple<Keyframe, Keyframe> closestKeyframes = GetClosestKeyframes(time);

		Keyframe first = std::get<0>(closestKeyframes);
		Keyframe second = std::get<1>(closestKeyframes);

		float dt = Duration(first.GetTime() - second.GetTime());

		float m0 = first.GetOutTangent() * dt;
		float m1 = second.GetInTangent() * dt;

		float t2 = t * t;
		float t3 = t2 * t;

		float a = 2 * t3 - 3 * t2 + 1;
		float b = t3 - 2 * t2 + t;
		float c = t3 - t2;
		float d = -2 * t3 + 3 * t2;

		return a * first.GetValue() + b * m0 + c * m1 + d * second.GetValue();
	}


	std::tuple<Keyframe, Keyframe> AnimationCurve::GetClosestKeyframes(Second time)
	{
		Keyframe first;
		Keyframe second;

	#if DEBUG
		bool keysAssigned = false;
	#endif
		for (int i = 0; i < _keyframes.size(); i++)
		{
			Keyframe keyframe = _keyframes[i];
			Second keyTime = keyframe.GetTime();

			if (keyTime <= time)
			{
				first = keyframe;
			}

			if (keyTime >= time)
			{
				second = keyframe;
			#if DEBUG
				keysAssigned = true;
			#endif
				break;
			}
		}

		ASSERT(keysAssigned);

		return std::tuple<Keyframe, Keyframe>(first, second);
	}
}