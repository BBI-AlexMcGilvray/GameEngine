#pragma once

#include "TimeDefs.h"

namespace Core
{
	struct Keyframe
	{
	public:
		Keyframe();
		Keyframe(Second time, float value);
		Keyframe(Second time, float value, float inWeight, float infloatangent, float outWeight, float outfloatangent);

		void SetTime(Second time);
		Second GetTime();

		void SetValue(float value);
		float GetValue();

		void SetInWeight(float weight);
		float GetInWeight();

		void SetInTangent(float tangent);
		float GetInTangent();

		void SetOutWeight(float weight);
		float GetOutWeight();

		void SetOutTangent(float tangent);
		float GetOutTangent();

	private:
		Second _time;
		float _value;

		float _inWeight;
		float _inTangent;

		float _outWeight;
		float _outTangent;
	};
}