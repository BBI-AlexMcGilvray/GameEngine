#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/ListDefs.h"

#include "Core/Functionality/Headers/Event.h"

#include "Pipeline/Rendering/3D/Headers/Bone.h"

#include "Data/Headers/AssetData.h"
#include "Data/Rendering/Headers/SkeletonData.h"

namespace Application {
namespace Rendering {
  struct Skeleton : Geometric::Node
  {
    // animation system and how we want to plug it in is TBD - presumably a more generic system than wiring it specific to bones and such
    //Core::List<BoneAnimation> Animations;

    // we will need the parent node in constructor to know where our bones are rooted to
    Skeleton(Core::Ptr<State> parentState, Core::Ptr<Geometric::Node> parentNode, Data::AssetName<Data::Rendering::SkeletonData> asset);

    int GetBoneCount() const;
    Core::Ptr<Bone> GetSkeletonHierarchy() const;

    int GetIndexOf(const String &nodeName) const;
    List<Float4x4> GetBoneMatrices() const;

  private:
    Data::AssetData<Data::Rendering::SkeletonData> Data;
    // unsure if we need the below two pieces of data
    Core::Functionality::Delegate<> OnRootDeleted;
    Core::Ptr<Bone> Root = nullptr;

    // hold list of all bones - in order - to be able to calculate the matrices to pass to shader in the same order
    std::vector<Core::Ptr<Bone>> BoneList;

    Core::Ptr<Bone> CreateBoneHeirarchy(Core::Ptr<Geometric::Node> parentNode, size_t& boneIndex, Core::Ptr<Bone> rootBone = nullptr);
  };
}// namespace Rendering
}// namespace Application