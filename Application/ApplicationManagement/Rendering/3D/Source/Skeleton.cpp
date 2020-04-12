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
		Bone::Bone(Core::Ptr<State> parentState, Core::String name, Float3 position, FQuaternion rotation, Float3 scale)
			: Node(parentState, name, position, rotation, scale)
			// initial position is the bind position
			, InverseBindMatrix(Transformation.GetInverseTransformationMatrix())
		{

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
			, OnRootDeleted{[this]()
		{
			Root = nullptr;

			return true;
		} }
		{
			LOG("BONE | PARENT | FINAL");
			Root = CreateBoneHeirarchy(parentNode, Data.Data.Root.get(), true);
			Root->Deleted += OnRootDeleted;
		}

		Core::Ptr<Bone> Skeleton::GetSkeletonHierarchy() const
		{
			VERIFY(Root != nullptr);
			return Root;
		}

		Core::Ptr<Bone> Skeleton::CreateBoneHeirarchy(Core::Ptr<Geometric::Node> parentNode, Core::Ptr<Data::Rendering::SkeletonBoneData> boneData, bool rootNode)
		{
			Float4x4 transformationMatrix = parentNode->Transformation.GetTransformationMatrix();
			Float3 deconstructedPosition;
			FQuaternion deconstructedRotation;
			Float3 deconstructredScale;
			TransformationMatrixDecomposition(transformationMatrix, deconstructedPosition, deconstructredScale, deconstructedRotation);

			// testing
			Float3 finalPosition = rootNode ? boneData->Position + deconstructedPosition : boneData->Position - deconstructedPosition;
			FQuaternion finalRotation = rootNode ? boneData->Rotation * deconstructedRotation : deconstructedRotation / boneData->Rotation;
			Float3 finalScale = rootNode ? boneData->Scale * deconstructredScale : boneData->Scale / deconstructredScale;

			LOG(boneData->Name);
			LOG("P: " + VectorString(boneData->Position) + " | " + VectorString(deconstructedPosition) + " | " + VectorString(finalPosition));
			//LOG("Q: " + QuaternionString(boneData->Rotation) + " | " + QuaternionString(deconstructedRotation) + " | " + QuaternionString(finalRotation));
			//LOG(VectorString(boneData->Scale) + " | " + VectorString(deconstructredScale) + " | " + VectorString(finalScale));

			finalScale = 1.0f;
			LOG("Should not be modifying scale on import");

			Ptr<Bone> newBone = parentNode->AddChild<Bone>(boneData->Name, finalPosition, finalRotation, finalScale);
			Push(BoneList, newBone);

			for (Core::size i = 0; i < boneData->ChildBones.size(); i++)
			{
				CreateBoneHeirarchy(newBone, boneData->ChildBones[i].get(), false);
			}

			return newBone;
		}
	}
}