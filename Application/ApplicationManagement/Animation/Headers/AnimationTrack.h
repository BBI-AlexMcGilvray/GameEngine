#pragma once

#include "Core/Headers/ListDefs.h"
#include "ApplicationManagement/Animation/Headers/AnimationCurve.h"

namespace Application
{
	namespace Animation
	{
		class AnimationTrack
		{
		private:
			float& _target;
			AnimationCurve _curve;

		public:
			AnimationTrack(float& target);
			AnimationTrack(float& target, AnimationCurve curve);
			// maybe a constructor to take a serialized animation curve?

			void SetCurve(AnimationCurve curve);
			AnimationCurve& GetCurve();

			void Update(Core::Second time);
		};
	}
}