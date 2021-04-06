/*#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

#include "ApplicationManagement/Animation/Headers/Animator.h"
//#include "ApplicationManagement/Animation/Animators/Headers/TransformationAnimator.h"

#include "ApplicationManagement/Rendering/3D/Headers/Skeleton.h"

namespace Application
{
	namespace Animation
	{
		class SkeletonAnimator : IAnimator
		{
		private:
			Data::AssetData<Data::Rendering::SkeletonAnimationData> Data;

			//Core::List<TransformationAnimator> _transformationAnimators;
			Core::Ptr<Rendering::Skeleton> _skeleton;

			void SetupTransformationAnimators();

		public:
			SkeletonAnimator(Core::Ptr<Rendering::Skeleton> skeleton, Data::AssetName<Data::Rendering::SkeletonAnimationData> asset);

			void Update(Core::Second dt);
		};
	}
}*/