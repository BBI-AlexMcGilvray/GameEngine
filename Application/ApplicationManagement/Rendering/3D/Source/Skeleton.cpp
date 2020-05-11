#include "ApplicationManagement/Rendering/3D/Headers/Skeleton.h"

#include "Core/Math/Headers/QuaternionFunctions.h"

#if _DEBUG
#include "Core/Headers/PtrDefs.h"
#include "Core/Math/Headers/MatrixFunctions.h"

#include "ApplicationManagement/Geometric/Headers/HierarchyComponent.h"
#include "ApplicationManagement/Geometric/Headers/ContentBase.h"

#include "ApplicationManagement/Headers/ApplicationManager.h"
#include "ApplicationManagement/Rendering/Headers/RenderComponent.h"
#include "ApplicationManagement/Rendering/3D/Headers/SphereRenderObject.h"

#include "Resources/Assets.h"
#endif

using namespace Core;
using namespace Core::Math;

namespace Application
{
	namespace Rendering
	{
		Bone::Bone(Core::Ptr<State> parentState, Ptr<Node> parentNode, Ptr<Bone> rootBone, Core::String name, Float3 position, FQuaternion rotation, Float3 scale)
			: Node(parentState, parentNode, name, position, rotation, scale, false)
		{
			// initial position is the bind position
			if (rootBone == nullptr)
			{
				InverseBindMatrix = Float4x4(II{});
			}
			else
			{
				InverseBindMatrix = Inverse(rootBone->Transformation.GetWorldInverseTransformationMatrix() * Transformation.GetWorldTransformationMatrix());
			}
		}

		void Bone::Start()
		{
#if _DEBUG
			Ptr<Geometric::ContentBase> debugContent = AddContent(MakeUnique<Geometric::ContentBase>());

			ComponentPtr<Geometric::Hierarchy> hierarchyComponent = debugContent->GetComponent<Geometric::Hierarchy>();
			ComponentPtr<Rendering::Render> renderComponent = debugContent->AddComponent<Rendering::Render>(ApplicationManager::AppRenderManager().GetObjectManagerForState(ParentState));
			
			renderComponent->AddRenderObject<Rendering::SphereRenderObject>(&(hierarchyComponent->GetHeirarchyNode()->Transformation), GREEN, 0.1f);
#endif
		}

		Float4x4 Bone::GetBindOffset()
		{
			return (InverseBindMatrix * Transformation.GetWorldTransformationMatrix());
		}

		List<Float4x4> Bone::GetBoneMatrices()
		{
			int boneCount = GetSubNodeCount();
			List<Float4x4> boneMatrices = List<Float4x4>(boneCount);

			Push(boneMatrices, GetBindOffset());
			for (int i = 0; i < Children.size(); i++)
			{
				Push(boneMatrices, ((Ptr<Bone>)Children[i].get())->GetBoneMatrices());
			}

			return boneMatrices;
		}

		Skeleton::Skeleton(Core::Ptr<Geometric::Node> parentNode, Data::AssetName<Data::Rendering::SkeletonData> asset)
			: Data(asset)
			, OnRootDeleted{[this]()
		{
			Root = nullptr;

			return true;
		} }
		{
			Root = CreateBoneHeirarchy(parentNode, Data.Data.Root.get());

			// fit root to node
			Root->Transformation.AdjustPosition(-1 * Root->Transformation.GetPosition());
			Root->Transformation.AdjustRotation(Root->Transformation.GetRotation().Inverse());

			Root->Deleted += OnRootDeleted;
		}

		int Skeleton::GetBoneCount() const
		{
			VERIFY(Root != nullptr);
			return Root->GetSubNodeCount();
		}

		Core::Ptr<Bone> Skeleton::GetSkeletonHierarchy() const
		{
			VERIFY(Root != nullptr);
			return Root;
		}

		List<Float4x4> Skeleton::GetBoneMatrices() const
		{
			VERIFY(Root != nullptr);
			return Root->GetBoneMatrices();
		}

		int Skeleton::GetIndexOf(String& const nodeName) const
		{
			return Root->GetChildDepth(nodeName);
		}

		Core::Ptr<Bone> Skeleton::CreateBoneHeirarchy(Core::Ptr<Geometric::Node> parentNode, Core::Ptr<Data::Rendering::SkeletonBoneData> boneData, Ptr<Bone> rootBone)
		{
			LOG("Setting bone to have scale of 1.0f instead of " + VectorString(boneData->Scale));
			Ptr<Bone> newBone = parentNode->AddChild<Bone>(rootBone, boneData->Name, boneData->Position, boneData->Rotation, 1.0f);// boneData->Scale);

			if (rootBone == nullptr)
			{
				rootBone = newBone;
			}

			Push(BoneList, newBone);

			for (Core::size i = 0; i < boneData->ChildBones.size(); i++)
			{
				CreateBoneHeirarchy(newBone, boneData->ChildBones[i].get(), rootBone);
			}

			return newBone;
		}
	}
}