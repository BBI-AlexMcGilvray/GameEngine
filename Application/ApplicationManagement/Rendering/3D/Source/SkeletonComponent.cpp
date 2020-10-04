#include "ApplicationManagement/Rendering/3D/Headers/SkeletonComponent.h"

namespace Application
{
	namespace Rendering
	{
		SkeletonComponent::SkeletonComponent(Core::Ptr<EntityBase> entity, Core::Ptr<AnimatedModel> animatedModel)
			: Component<SkeletonComponent>(entity, this)
		{

		}
	}
}