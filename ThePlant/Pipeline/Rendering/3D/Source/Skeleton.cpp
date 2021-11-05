#include "Pipeline/Rendering/3D/Headers/Skeleton.h"

#include "Core/Math/Headers/QuaternionFunctions.h"
#include "Core/Logging/Logger.h"

#include "Pipeline/Headers/ApplicationManager.h"

using namespace Core;
using namespace Core::Math;

namespace Application {
namespace Rendering {
  Skeleton::Skeleton(Core::Ptr<State> parentState, Core::Ptr<Geometric::Node> parentNode, Data::AssetName<Data::Rendering::SkeletonData> asset)
    : Geometric::Node(parentState, parentNode), Data(ApplicationManager::AppAssetManager().getAssetData(asset)), OnRootDeleted{ [this]() {
        Root = nullptr;

        return true;
      } }
  {
    size_t startIndex = 0;
    Root = CreateBoneHeirarchy(parentNode, startIndex);

    // fit root to node
    Root->Transformation.AdjustLocalPosition(-1 * Root->Transformation.GetLocalPosition());
    Root->Transformation.AdjustLocalRotation(Root->Transformation.GetLocalRotation().Inverse());

    Root->Deleted += OnRootDeleted;
  }

  int Skeleton::GetBoneCount() const
  {
    VERIFY(Root != nullptr);
    return Root->GetSubNodeCount() + 1;
  }

  Core::Ptr<Bone> Skeleton::GetSkeletonHierarchy() const
  {
    VERIFY(Root != nullptr);
    return Root;
  }

  List<Core::Math::Float4x4> Skeleton::GetBoneMatrices() const
  {
    VERIFY(Root != nullptr);
    int initialOffset = 0;
    List<Core::Math::Float4x4> boneMatrices = List<Core::Math::Float4x4>(GetBoneCount());
    Root->GetBoneMatrices(boneMatrices, initialOffset);
    return boneMatrices;
  }

  int Skeleton::GetIndexOf(const String &nodeName) const
  {
    return ((Ptr<Bone>)Root)->GetBoneIndex(nodeName);
  }

  Core::Ptr<Bone> Skeleton::CreateBoneHeirarchy(Core::Ptr<Geometric::Node> parentNode, size_t& boneIndex, Ptr<Bone> rootBone)
  {
    const Data::Rendering::SkeletonBoneData& boneData = Data->bones[boneIndex];
    CORE_LOG("Skeleton", "Setting bone to have scale of 1.0f instead of " + VectorString(boneData.scale));

    Ptr<Bone> newBone = parentNode->AddChild<Bone>(rootBone, boneData.name, boneData.position, boneData.rotation, 1.0f);// boneData->Scale);

    if (rootBone == nullptr) {
      rootBone = newBone;
    }

    Push(BoneList, newBone);

    for (uint i = 0; i < boneData.children; i++) {
      CreateBoneHeirarchy(newBone, ++boneIndex, rootBone);
    }

    return newBone;
  }
}// namespace Rendering
}// namespace Application