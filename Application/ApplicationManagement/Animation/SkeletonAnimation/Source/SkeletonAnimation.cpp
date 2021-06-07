#include "ApplicationManagement/Animation/SkeletonAnimation/Headers/SkeletonAnimation.h"

namespace Application
{
	namespace Animation
	{
		SkeletonAnimation::SkeletonAnimation(Data::AssetName<Data::Rendering::SkeletonAnimationData> data)
			: _data(data)
			, _track(_data)
		{

		}

		void SkeletonAnimation::Evaluate(Core::Second time)
		{
			_evaluationResults = _track.Evaluate(time);
		}

		Map<string, Transform> SkeletonAnimation::GetAnimationResults()
		{
			return _evaluationResults;
		}
	}
}