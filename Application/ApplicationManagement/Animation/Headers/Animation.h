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
			// events can be handled by a specialized animation track that fires events with a given identifier (hash) when a keyframe is hit
			// would also required a specialized keyframe
			Core::List<AnimationTrack<T> _tracks;

		public:
			Animation();

			T Evaluate(Core::Second time);
		};
	}
}