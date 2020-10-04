#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

#include "ApplicationManagement/Animation/Headers/AnimationTrack.h"

namespace Application
{
	namespace Animation
	{
		template <typename T>
		class Animatable;

		template <typename T>
		class AnimationMixer
		{
			Core::Ptr<Animatable<T>> _animatable;

		public:
			AnimationMixer();

			void MixValue(float weight, T value);
		};
	}
}