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
    Root = CreateBoneHeirarchy(parentNode, Data->root.get());

    // fit root to node
    Root->Transformation.AdjustPosition(-1 * Root->Transformation.GetPosition());
    Root->Transformation.AdjustRotation(Root->Transformation.GetRotation().Inverse());

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

  List<Float4x4> Skeleton::GetBoneMatrices() const
  {
    VERIFY(Root != nullptr);
    int initialOffset = 0;
    List<Float4x4> boneMatrices = List<Float4x4>(GetBoneCount());
    Root->GetBoneMatrices(boneMatrices, initialOffset);
    return boneMatrices;
  }

  int Skeleton::GetIndexOf(const String &nodeName) const
  {
    return ((Ptr<Bone>)Root)->GetBoneIndex(nodeName);
  }

  Core::Ptr<Bone> Skeleton::CreateBoneHeirarchy(Core::Ptr<Geometric::Node> parentNode, Core::Ptr<Data::Rendering::SkeletonBoneData> boneData, Ptr<Bone> rootBone)
  {
    DEBUG_LOG("Skeleton", "Setting bone to have scale of 1.0f instead of " + VectorString(boneData->scale));
    Ptr<Bone> newBone = parentNode->AddChild<Bone>(rootBone, boneData->name, boneData->position, boneData->rotation, 1.0f);// boneData->Scale);

    if (rootBone == nullptr) {
      rootBone = newBone;
    }

    Push(BoneList, newBone);

    for (Core::size i = 0; i < boneData->childBones.size(); i++) {
      CreateBoneHeirarchy(newBone, boneData->childBones[i].get(), rootBone);
    }

    return newBone;
  }
}// namespace Rendering
}// namespace Application