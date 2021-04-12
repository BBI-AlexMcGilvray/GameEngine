#include "ApplicationManagement/Animation/SkeletonAnimation/Headers/SkeletonAnimationTrack.h"

#include "Core/Debugging/Headers/Macros.h"

#include "ApplicationManagement/Geometric/Headers/Node.h"
#include "ApplicationManagement/Rendering/3D/Headers/Bone.h"

namespace Application
{
	namespace Animation
	{
		SkeletonAnimationTrack::SkeletonAnimationTrack()
		{}

		void SkeletonAnimationTrack::SetTrack(int boneIndex, TransformAnimationTrack animationTrack)
		{
			if (!Core::In(_tracks, boneIndex))
			{
				_tracks[boneIndex] = animationTrack;
			}

			ALERT("Bone index " + std::to_string(boneIndex) + " already being affected by an animationtrack");
		}

		void SkeletonAnimationTrack::SetStartState(const Rendering::Skeleton& skeleton)
		{
			Core::Ptr<Rendering::Bone> hierarchy = skeleton.GetSkeletonHierarchy();
			CreateStartState(hierarchy, 0);
		}

		Core::List<Transform> SkeletonAnimationTrack::Evaluate(Core::Second time)
		{
			Core::List<Transform> skeleton(_tracks.size());

			for (Core::Pair<const int, TransformAnimationTrack>& pair : _tracks)
			{
				skeleton[pair.first] = pair.second.Evaluate(time);
			}

			return skeleton;
		}

		int SkeletonAnimationTrack::CreateStartState(Core::Ptr<Geometric::Node> rootBone, int index)
		{
			_startState[index] = rootBone->Transformation;

			int offset = 0;
			for (Core::Ptr<Geometric::Node> child : rootBone->GetChildren())
			{
				offset++;
				offset += CreateStartState(child, index + offset);
			}

			return offset;
		}
	}
}