#include "Pipeline/Rendering/3D/Headers/Bone.h"

#include "Core/Math/Headers/MatrixFunctions.h"

#if _DEBUG
#include "Pipeline/Headers/ApplicationManager.h"

#include "Pipeline/Geometric/Headers/HierarchyComponent.h"
#include "Pipeline/Geometric/Headers/ContentBase.h"

#include "Pipeline/Rendering/3D/Headers/SphereRenderObject.h"
#endif

namespace Application {
namespace Rendering {
  Bone::Bone(Core::Ptr<State> parentState, Ptr<Node> parentNode, Ptr<Bone> rootBone, std::string name, Core::Math::Float3 position, Core::Math::FQuaternion rotation, Core::Math::Float3 scale)
    : Node(parentState, parentNode, name, position, rotation, scale, false), RootBone(rootBone)
  {
    // initial position is the bind position
    if (rootBone == nullptr) {
      // InverseBindMatrix is the initial binding offset between the root node and the current node. For the root node, this is always 0
      InverseBindMatrix = Core::Math::Float4x4(II{});
    } else {
      InverseBindMatrix = Core::Math::Inverse(rootBone->Transformation.GetWorldInverseTransformationMatrix() * Transformation.GetWorldTransformationMatrix());
    }

#if _DEBUG
    // This is a useless verification as the == operator will likely never be EXACT in this case - need a 'within range' equator
    //if (!VERIFY(GetBindOffset() == Float4x4(II{})))
    //{
    //	LOG(Name + " does not have a valid bind matrix: " + MatrixString(GetBindOffset()));
    //}
#endif
  }

  void Bone::Start()
  {
#if _DEBUG
    Ptr<Geometric::ContentBase> debugContent = AddContent(MakeUnique<Geometric::ContentBase>(ParentState));

    ComponentPtr<Geometric::Hierarchy> hierarchyComponent = debugContent->GetComponent<Geometric::Hierarchy>();
    ComponentPtr<Rendering::Render> renderComponent = debugContent->AddComponent<Rendering::Render>(ApplicationManager::AppRenderManager().GetObjectManagerForState(ParentState));

    renderComponent->SetRenderObject<Rendering::SphereRenderObject>(&(hierarchyComponent->GetHeirarchyNode()->Transformation), GREEN, 0.3f);
#endif
  }

  Core::Math::Float4x4 Bone::GetBindOffset()
  {
    if (RootBone != nullptr) {
      return RootBone->Transformation.GetWorldInverseTransformationMatrix() * Transformation.GetWorldTransformationMatrix() * InverseBindMatrix;
    } else {
      // Since this is the root node, the InverseBindMatrix is always 0, so we are essentially just forwarding in the transform itself (to accound for the node being moved at all)
      return Transformation.GetLocalTransformationMatrix() * InverseBindMatrix;
    }
  }

  // Problem was: was returning the depth, but the way it was calculated is not equivalent to bone INDEX
  // New Problem: Keeps counting forever, need to break out of the recursion when a bone is found
  int Bone::GetBoneIndex(std::string name)
  {
    bool indexFound = false;
    int index = GetBoneIndex(name, indexFound);

    if (!indexFound)
    {
      CORE_ERROR("Bone", "Unable to find bone <" + name + ">");
    }

    return (indexFound ? index : -1);
  }

  void Bone::GetBoneMatrices(std::vector<Core::Math::Float4x4> &boneMatrices, int &offset)
  {
    boneMatrices[offset] = GetBindOffset();
    for (int i = 0; i < Children.size(); i++) {
      ((Ptr<Bone>)Children[i].get())->GetBoneMatrices(boneMatrices, ++offset);
    }
  }

  int Bone::GetBoneIndex(std::string name, bool &indexFound)
  {
    if (Name == name) {
      indexFound = true;
      return 0;
    }

    int depth = 1;

    for (Core::size i = 0; i < Children.size(); i++) {
      int childDepth = ((Ptr<Bone>)Children[i].get())->GetBoneIndex(name, indexFound);
      depth += childDepth;
      if (childDepth == 0 || indexFound) {
        break;
      }
    }

    return depth;
  }
}// namespace Rendering
}// namespace Application