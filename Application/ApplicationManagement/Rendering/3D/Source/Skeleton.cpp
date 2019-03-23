#include "ApplicationManagement/Rendering/3D/Headers/Skeleton.h"

#include "Core/Math/Headers/QuaternionFunctions.h"

#if _DEBUG
#include "Core/Headers/PtrDefs.h"

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
		Bone::Bone(Core::Ptr<State> parentState/*, Float4x4 inverseBindMatrix*/, Core::String name, Float3 position, FQuaternion rotation, Float3 scale)
			: Node(parentState, name, position, rotation, scale)
			//, InverseBindMatrix(inverseBindMatrix)
		{
			Transformation.SetLocal(false);
		}

		void Bone::Start()
		{
#if _DEBUG
			Ptr<Geometric::ContentBase> debugContent = AddContent(MakeUnique<Geometric::ContentBase>());

			ComponentPtr<Geometric::Hierarchy> hierarchyComponent = debugContent->GetComponent<Geometric::Hierarchy>();
			ComponentPtr<Rendering::Render> renderComponent = debugContent->AddComponent<Rendering::Render>(ApplicationManager::AppRenderManager().GetObjectManagerForState(ParentState));
			
			Float3 position = Transformation.GetPosition();
			renderComponent->AddRenderObject<Rendering::SphereRenderObject>(&(hierarchyComponent->GetHeirarchyNode()->Transformation), GREEN, 0.1f);
#endif
		}

		Skeleton::Skeleton(Core::Ptr<Geometric::Node> parentNode, Data::AssetName<Data::Rendering::SkeletonData> asset)
			: Data(asset)
			, OnRootDeleted{ [this]()
		{
			Root = nullptr;

			return true;
		} }
		{
			Root = CreateBoneHeirarchy(parentNode, Data.Data.Root.get());
			Root->Deleted += OnRootDeleted;
		}

		Core::Ptr<Bone> Skeleton::GetSkeletonHierarchy() const
		{
			VERIFY(Root != nullptr);
			return Root;
		}

		Core::Ptr<Bone> Skeleton::CreateBoneHeirarchy(Core::Ptr<Geometric::Node> parentNode, Core::Ptr<Data::Rendering::SkeletonBoneData> boneData)
		{
			// need to determine if assimp values are relative (local) or not (global)
			Float3 finalPosition = boneData->Position;// parentNode->Transformation.GetPosition() + boneData->Position;
			FQuaternion finalRotation = boneData->Rotation;// *parentNode->Transformation.GetRotation();
			Float3 finalScale = boneData->Scale;// parentNode->Transformation.GetScale() * boneData->Scale;
			finalScale = 1.0f;
			LOG("Should not be modifying scale on import");

			Ptr<Bone> newBone = parentNode->AddChild<Bone>(boneData->Name, finalPosition, finalRotation, finalScale);
			Push(BoneList, newBone);

			for (Core::size i = 0; i < boneData->ChildBones.size(); i++)
			{
				CreateBoneHeirarchy(newBone, boneData->ChildBones[i].get());
			}

			return newBone;
		}
	}
}