#pragma once

#include "ApplicationManagement/Animation/Headers/Animatable.h"

#include "ApplicationManagement/Rendering/3D/Headers/Skeleton.h"

namespace Application {
namespace Animation {
  // implementations should create a mixer and hold a reference/the logic for applying the animation to the animatable object
  class SkeletonAnimatable : public Animatable
  {
  public:
    SkeletonAnimatable() = default;// ideally this doesn't exist, but postponing fixing until the dependencies are fixed (whatever makes this should have the data for it, and currently model has it but the data is in the skeleton)
    SkeletonAnimatable(Rendering::Skeleton &target);
    SkeletonAnimatable(const SkeletonAnimatable &other);

    SkeletonAnimatable &operator=(const SkeletonAnimatable &other);

    Rendering::Skeleton &GetTarget() const;

    void CreateMixer() override;

  private:
    // ideally would be a reference, but not sure if we want skeletons to be copy-able/assignable
    Ptr<Rendering::Skeleton> _target;
  };
}// namespace Animation
}// namespace Application
