#include "Core/Headers/Keyframe.h"

namespace Core
{
	Keyframe::Keyframe()
		: Keyframe(Second(0), float(0), 0.5f, 0.0f, 0.5f, 0.0f)
	{}

	Keyframe::Keyframe(Second time, float value)
		: Keyframe(time, value, 0.5f, 0.0f, 0.5f, 0.0f)
	{}

	Keyframe::Keyframe(Second time, float value, float inWeight, float inTangent, float outWeight, float outTangent)
		: _time(time), _value(value), _inWeight(inWeight), _inTangent(inTangent), _outWeight(outWeight), _outTangent(outTangent)
	{}

	void Keyframe::SetTime(Second time)
	{
		_time = time;
	}

	Second Keyframe::GetTime()
	{
		return _time;
	}

	void Keyframe::SetValue(float value)
	{
		_value = value;
	}

	float Keyframe::GetValue()
	{
		return _value;
	}

	void Keyframe::SetInWeight(float weight)
	{
		_inWeight = weight;
	}

	float Keyframe::GetInWeight()
	{
		return _inWeight;
	}

	void Keyframe::SetInTangent(float tangent)
	{
		_inTangent = tangent;
	}

	float Keyframe::GetInTangent()
	{
		return _inTangent;
	}

	void Keyframe::SetOutWeight(float weight)
	{
		_outWeight = weight;
	}

	float Keyframe::GetOutWeight()
	{
		return _outWeight;
	}

	void Keyframe::SetOutTangent(float tangent)
	{
		_outTangent = tangent;
	}

	float Keyframe::GetOutTangent()
	{
		return _outTangent;
	}
}