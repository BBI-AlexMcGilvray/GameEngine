#include "ApplicationManagement/Animation/FieldAnimation/Headers/FloatAnimationTrack.h"

namespace Application
{
	namespace Animation
	{
		FloatAnimationTrack::FloatAnimationTrack(AnimationCurve curve)
			: _curve(curve)
		{

		}

		void FloatAnimationTrack::SetCurve(AnimationCurve curve)
		{
			_curve = curve;
		}

		AnimationCurve& FloatAnimationTrack::GetCurve()
		{
			return _curve;
		}

		float FloatAnimationTrack::Evaluate(Core::Second time)
		{
			return _curve.Evaluate(time);
		}
	}
}