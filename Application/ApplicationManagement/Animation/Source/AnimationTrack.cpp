#include "ApplicationManagement/Animation/Headers/AnimationTrack.h"

namespace Application
{
	namespace Animation
	{
		AnimationTrack::AnimationTrack(float& target)
			: _target(target)
		{

		}

		AnimationTrack::AnimationTrack(float& target, AnimationCurve curve)
			: _target(target)
			, _curve(curve)
		{

		}

		void AnimationTrack::SetCurve(AnimationCurve curve)
		{
			_curve = curve;
		}

		AnimationCurve& AnimationTrack::GetCurve()
		{
			return _curve;
		}

		void AnimationTrack::Update(Core::Second time)
		{
			_target = _curve.Evaluate(time);
		}
	}
}