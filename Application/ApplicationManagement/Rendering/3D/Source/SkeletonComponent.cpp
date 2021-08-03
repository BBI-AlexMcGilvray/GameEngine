#include "ApplicationManagement/Rendering/3D/Headers/SkeletonComponent.h"

#include "Core/Debugging/Headers/Macros.h"

namespace Application {
namespace Rendering {
  SkeletonComponent::SkeletonComponent(Core::Ptr<EntityBase> entity)
    : Component<SkeletonComponent>(entity, this)
  {
  }

  const Core::Ptr<Skeleton> SkeletonComponent::GetSkeleton()
  {
    return _skeleton;
  }

  Core::Ptr<Skeleton> SkeletonComponent::SetSkeleton(Core::Ptr<Skeleton> skeleton)
  {
    _skeleton = skeleton;

    return _skeleton;
  }

  void SkeletonComponent::RemoveSkeleton(Core::Ptr<Skeleton> skeleton)
  {
    ASSERT(_skeleton == skeleton);

    _skeleton = nullptr;
  }
}// namespace Rendering
}// namespace Application