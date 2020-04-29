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
		Bone::Bone(Core::Ptr<State> parentState, Ptr<Node> parentNode, Core::String name, Float3 position, FQuaternion rotation, Float3 scale)
			: Node(parentState, parentNode, name, position, rotation, scale, false)
			// initial position is the bind position
			, InverseBindMatrix(Transformation.GetWorldInverseTransformationMatrix())
		{

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

		Skeleton::Skeleton(Core::Ptr<Geometric::Node> parentNode, Data::AssetName<Data::Rendering::SkeletonData> asset)
			: Data(asset)
			, OnRootDeleted{[this]()
		{
			Root = nullptr;

			return true;
		} }
		{
			Root = CreateBoneHeirarchy(parentNode, Data.Data.Root.get(), true);
			LOG(VectorString(Root->Transformation.GetWorldPosition()));
			LOG(VectorString(parentNode->Transformation.GetWorldPosition()));
			Root->Transformation.AdjustPosition(-1 * (parentNode->Transformation.GetWorldPosition()));
			LOG(VectorString(Root->Transformation.GetWorldPosition()));
			Root->Deleted += OnRootDeleted;
		}

		Core::Ptr<Bone> Skeleton::GetSkeletonHierarchy() const
		{
			VERIFY(Root != nullptr);
			return Root;
		}

		Core::Ptr<Bone> Skeleton::CreateBoneHeirarchy(Core::Ptr<Geometric::Node> parentNode, Core::Ptr<Data::Rendering::SkeletonBoneData> boneData, bool rootNode)
		{
			Ptr<Bone> newBone = parentNode->AddChild<Bone>(boneData->Name, boneData->Position, boneData->Rotation, 1.0f);// boneData->Scale);

			Push(BoneList, newBone);

			for (Core::size i = 0; i < boneData->ChildBones.size(); i++)
			{
				CreateBoneHeirarchy(newBone, boneData->ChildBones[i].get(), false);
			}

			return newBone;
		}
	}
}