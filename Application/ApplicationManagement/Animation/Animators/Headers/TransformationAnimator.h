#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

#include "ApplicationManagement/Animation/Headers/AnimationTrack.h"
#include "ApplicationManagement/Animation/Headers/Animator.h"
#include "ApplicationManagement/Animation/Headers/Animatable.h"

#include "Core/Geometric/Headers/Transform.h"

namespace Application
{
	namespace Animation
	{
		class TransformationAnimator : IAnimator
		{
		private:
			Vector3<float> _vectorAnimator;
			Quaternion<float> _quaternionAnimator;

		public:
			TransformationAnimator(Core::Ptr<Core::Geometric::Transform> transform);

			void Update(Core::Second dt);
		};
	}
}