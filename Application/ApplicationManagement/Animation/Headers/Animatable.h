#pragma once

#include "Core/Headers/PtrDefs.h"

namespace Application
{
	// is this useful? it does allow us to have multiple systems interact with a single object through the same mixer...
	// current problem is with the fact that we would have circular dependencies due to templates
	// alternative to templates is to have it be implementations instead of templates
	namespace Animation
	{
		class AnimationMixer;

		// implementations should create a mixer and hold a reference/the logic for applying the animation to the animatable object
		class Animatable
		{
		private:
			Core::UniquePtr<AnimationMixer> _mixer = nullptr;

		public:
			Animatable();
			~Animatable() = default;

			virtual void CreateMixer() = 0;
			Core::Ptr<AnimationMixer> GetMixer();
		};
	}
}