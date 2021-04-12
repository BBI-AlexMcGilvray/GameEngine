#pragma once

#include "Core/Headers/Hash.h"

#include "ApplicationManagement/Animation/TransformAnimation/Headers/TransformAnimationTrack.h"
#include "ApplicationManagement/Rendering/3D/Headers/Skeleton.h"

namespace Application
{
	namespace Animation
	{
		class SkeletonAnimationTrack
		{
		public:
			SkeletonAnimationTrack();
			// maybe a constructor to take a serialized animation curve?

			void SetTrack(int boneIndex, TransformAnimationTrack animationTrack);

			void SetStartState(const Rendering::Skeleton& skeleton);
			Core::List<Transform> Evaluate(Core::Second time);

		private:
			Core::List<Transform> _startState;

			// <bone index, animation track>
			Core::Map<int, TransformAnimationTrack> _tracks;

			int CreateStartState(Core::Ptr<Geometric::Node> rootBone, int index);
		};
	}
}