#include "ApplicationManagement/Animation/SkeletonAnimation/Headers/SkeletonAnimationMixer.h"

#include "ApplicationManagement/Animation/SkeletonAnimation/Headers/SkeletonAnimation.h"

namespace Application
{
	namespace Animation
	{
		SkeletonAnimationMixer::SkeletonAnimationMixer(SkeletonAnimatable& target)
			: AnimationMixer(&target)
			, _target(target)
		{}

		// up to implementations to cast animation into specific animation types
		void SkeletonAnimationMixer::MixAnimation(float weight, Core::Ptr<Animation> value, Core::Second animationTime)
		{
			value->Evaluate(animationTime);
			Push(_animationsToMix, MixData(weight, static_cast<SkeletonAnimation*>(value)->GetAnimatinResults()));
		}

		void SkeletonAnimationMixer::Apply()
		{
			Map<string, Transform> mixedTransforms;

			for (MixData mix : _animationsToMix)
			{
				for (Pair<const string, Transform>& transform : mix.transforms)
				{
					if (!In(mixedTransforms, transform.first))
					{
						mixedTransforms[transform.first] = Transform();
					}

					Transform& combinedTransform = mixedTransforms[transform.first];

					combinedTransform.AdjustPosition(transform.second.GetPosition() * mix.weight);
					combinedTransform.AdjustRotation(transform.second.GetRotation() * mix.weight);
					combinedTransform.AdjustScale(transform.second.GetScale() * mix.weight);
				}
			}

			for (Pair<const string, Transform>& transform : mixedTransforms)
			{
				_target.GetTarget().GetSkeletonHierarchy()->GetChild(transform.first)->Transformation.SetPosition(transform.second.GetPosition());
				_target.GetTarget().GetSkeletonHierarchy()->GetChild(transform.first)->Transformation.SetRotation(transform.second.GetRotation());
				_target.GetTarget().GetSkeletonHierarchy()->GetChild(transform.first)->Transformation.SetScale(transform.second.GetScale());
			}
		}
	}
}