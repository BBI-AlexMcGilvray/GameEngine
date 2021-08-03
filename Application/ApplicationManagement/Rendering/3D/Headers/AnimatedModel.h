#pragma once

#include "ApplicationManagement/Animation/Headers/AnimatorComponent.h"
#include "ApplicationManagement/Animation/SkeletonAnimation/Headers/SkeletonAnimatable.h"

#include "ApplicationManagement/Geometric/Headers/ContentBase.h"
#include "ApplicationManagement/Geometric/Headers/Node.h"

#include "ApplicationManagement/Rendering/Shaders/Headers/SkinnedObjectShader.h"

#include "ApplicationManagement/Rendering/2D/Headers/MaterialComponent.h"
#include "ApplicationManagement/Rendering/3D/Headers/SkeletonComponent.h"
#include "ApplicationManagement/Rendering/Headers/RenderComponent.h"

#include "Data/Headers/AssetData.h"
#include "Data/Rendering/Headers/AnimatedModelData.h"

namespace Application {
namespace Rendering {
  // is a model,  but also has a list of timelines that can be called for animations
  // also holds a list of the relevant bones
  struct AnimatedModel : public Geometric::ContentBase
  {
    Data::AssetData<Data::Rendering::AnimatedModelData> Data;

    AnimatedModel(const Core::Ptr<State> owningState, Core::Ptr<Geometric::Node> parentNode, Data::AssetName<Data::Rendering::AnimatedModelData> asset);

    // be able to change what skeleton a model is listening to - returns true if able to map to skeleton
    bool SkinToSkeleton(Core::Ptr<Skeleton> skeleton);

    void Initialize() override;
    void Start() override;
    void Update(Core::Second dt) override;
    void End() override;
    void CleanUp() override;

  private:
    ComponentPtr<SkeletonComponent> _skeletonComponent;
    ComponentPtr<MaterialComponent> _materialComponent;
    ComponentPtr<Render> _renderComponent;
    ComponentPtr<Animation::AnimatorComponent> _animatorComponent;
    Animation::SkeletonAnimatable _animatable;
  };
}// namespace Rendering
}// namespace Application