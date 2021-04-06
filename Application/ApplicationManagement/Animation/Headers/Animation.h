#pragma once

#include "Core/Headers/ListDefs.h"

#include "ApplicationManagement/Animation/Headers/AnimationTrack.h"

namespace Application
{
	namespace Animation
	{
		class Animation
		{
		private:
			// events can be handled by a specialized animation track that fires events with a given identifier (hash) when a keyframe is hit
			// would also required a specialized keyframe
			Core::List<AnimationTrack> _tracks;

			// having a completely independent variable we modify allows us to ensure it is always in the desired animation state
			// it also forces each animation to contain a track for each field in the value (can be a single keyframe)
			// T _animatedValue;

		public:
			Animation()
			{
				// setup all tracks to be referencing their respective fields in the animated value
			}

			virtual void Update(Core::Second time)
			{
				for (AnimationTrack<T> track : _tracks)
				{
					track.Update(time);
				}

				return _animatedValue;
			}

		protected:
			virtual void AddTrack(float& target, AnimationCurve curve) = 0;
		};
	}
}