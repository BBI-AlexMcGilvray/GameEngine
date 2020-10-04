#pragma once

#include "Core/Headers/ListDefs.h"

#include "ApplicationManagement/Animation/Headers/AnimationTrack.h"

namespace Application
{
	namespace Animation
	{
		template <typename T>
		class Animation
		{
		private:
			Core::List<AnimationTrack<T> _tracks;

		public:
			Animation();

			T Evaluate(Core::Second time);
		};
	}
}