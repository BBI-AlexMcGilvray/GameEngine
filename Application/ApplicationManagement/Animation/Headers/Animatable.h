#pragma once

#include "Core/Headers/PtrDefs.h"

#include "ApplicationManagement/Animation/Headers/AnimationMixer.h"

namespace Application
{
	namespace Animation
	{
		class IAnimator;

		template <typename T>
		class Animatable
		{
		private:
			T& _animatedT;
			AnimationMixer<T> _mixer;

		public:
			Animatable(T& animatedT);

			AnimationMixer<T> GetMixer();
			void SetValue(T animatedValue);
		};
	}
}