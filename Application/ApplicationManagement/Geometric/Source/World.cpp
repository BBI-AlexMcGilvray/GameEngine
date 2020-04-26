#include "ApplicationManagement/Geometric/Headers/World.h"

#include "ApplicationManagement/Headers/ApplicationManager.h"

#include "ApplicationManagement/Geometric/Headers/CameraNode.h"

#if _DEBUG
#include "ApplicationManagement/Geometric/Headers/ContentBase.h"
#include "ApplicationManagement/Geometric/Headers/HierarchyComponent.h"
#include "ApplicationManagement/Rendering/Headers/RenderComponent.h"
#include "ApplicationManagement/Rendering/3D/Headers/SphereRenderObject.h"

// testing
#include "ApplicationManagement/Rendering/Headers/RenderComponent.h"
#include "ApplicationManagement/Rendering/3D/Headers/ModelBase.h"
#include "ApplicationManagement/Rendering/3D/Headers/AnimatedModel.h"
#include "Resources/Assets.h"

#include "Core/Math/Headers/UtilityFunctions.h"
#include "Core/Math/Headers/MatrixFunctions.h"
#endif

namespace Application
{
	namespace Geometric
	{
		World::World(Ptr<State> parentState)
			: Scene(parentState)
		{
			Ptr<CameraNode> cameraNode = AddChild<CameraNode>(ApplicationManager::AppRenderManager(), 1280.0f / 1080.0f);
			// camera position not acting correctly in final transformation matrix (from camera)
			cameraNode->Transformation.SetPosition(Float3(0.0f, 0.0f, 20.0f));
			cameraNode->CameraComponent->GetCamera()->LookAt(Float3(0.0f, 0.0f, 0.0f));
		}

		void World::Start()
		{
			// just for testing currently
			FQuaternion q1 = FQuaternion(0.707107f, -0.707107f, 0.000000f, 0.000000f);
			FQuaternion q2 = FQuaternion();
			FQuaternion q3 = q1 * q2;
			FQuaternion q4 = q3 / q1;
			FQuaternion q5 = q1 / q2;
			LOG(QuaternionString(q3));
			LOG(QuaternionString(q4));
			LOG(QuaternionString(q5));

			FQuaternion q6 = FQuaternion(-0.383f, -0.003f, -0.876f, 0.292f);
			FQuaternion q7 = FQuaternion(-0.3832537f, 0.003002f, 0.8765803f, -0.2921934f);
			LOG(QuaternionString(q2 / q6));
			LOG(QuaternionString(q7 * q6));

			//Ptr<Node> staticMeshNode = AddChild<Node>("StaticMesh", Float3(-10.0f, 0.0f, 0.0f));
			//Ptr<ContentBase> staticMeshContent = staticMeshNode->AddContent(MakeUnique<ContentBase>());
			//ComponentPtr<Hierarchy> staticHierarchyComponent = staticMeshContent->GetComponent<Hierarchy>();
			//ComponentPtr<Rendering::Render> staticRenderComponent = staticMeshContent->AddComponent<Rendering::Render>(ApplicationManager::AppRenderManager().GetObjectManagerForState(ParentState));
			//staticRenderComponent->AddRenderObject<Rendering::ModelBase>(&(staticHierarchyComponent->GetHeirarchyNode()->Transformation), Data::Ast.spmdl.MI_0);

			holderNode = AddChild<Node>("Holder", Float3(0.0f, 5.0f, 0.0f), FQuaternion(1.0f, 0.0f, 0.0f, 0.0f), Float3(1.3f));
			LOG("holderNode WorldPosition = " + VectorString(holderNode->Transformation.GetWorldPosition()));
			LOG("holderNode WorldRotation = " + QuaternionString(holderNode->Transformation.GetWorldRotation()));
			LOG("holderNode WorldScale = " + VectorString(holderNode->Transformation.GetWorldScale()));
			
			Ptr<Node> animatedMeshNode = holderNode->AddChild<Node>("AnimatedMesh", Float3(0.0f, 3.0f, 0.0f), FQuaternion(II{}), Float3(1.5f), true);
			LOG("animatedMeshNode WorldPosition = " + VectorString(animatedMeshNode->Transformation.GetWorldPosition()));
			LOG("animatedMeshNode WorldRotation = " + QuaternionString(animatedMeshNode->Transformation.GetWorldRotation()));
			LOG("animatedMeshNode WorldScale = " + VectorString(animatedMeshNode->Transformation.GetWorldScale()));

			Float4x4 animatedMeshNodeTransformationMatrix = animatedMeshNode->Transformation.GetWorldTransformationMatrix();
			Float3 position;
			FQuaternion rotation;
			Float3 scale;
			TransformationMatrixDecomposition(animatedMeshNodeTransformationMatrix, position, scale, rotation);
			LOG("animatedMeshNode transformation position = " + VectorString(position));
			LOG("animatedMeshNode transformation rotation = " + QuaternionString(rotation));
			LOG("animatedMeshNode transformation scale = " + VectorString(scale));
			
			//Ptr<ContentBase> animatedMeshContent = animatedMeshNode->AddContent(MakeUnique<ContentBase>());
			//ComponentPtr<Rendering::Render> animatedRenderComponent = animatedMeshContent->AddComponent<Rendering::Render>(ApplicationManager::AppRenderManager().GetObjectManagerForState(ParentState));
			//animatedRenderComponent->AddRenderObject<Rendering::AnimatedModel>(animatedMeshNode, Data::Ast.amdl.Woman_0);
			//end of testing

			ContainerBase::Start();

			for (auto& child : Children)
			{
				child->Start();
			}

#if _DEBUG
			// debug
			Ptr<ContentBase> debugContent = AddContent(MakeUnique<ContentBase>());

			ComponentPtr<Hierarchy> hierarchyComponent = debugContent->GetComponent<Hierarchy>();
			ComponentPtr<Rendering::Render> renderComponent = debugContent->AddComponent<Rendering::Render>(ApplicationManager::AppRenderManager().GetObjectManagerForState(ParentState));

			renderComponent->AddRenderObject<Rendering::SphereRenderObject>(&(hierarchyComponent->GetHeirarchyNode()->Transformation), BLACK, 0.5f);
#endif
		}

		// debugging
		void World::Update(Second dt)
		{
			// just for testing currently
			FQuaternion currentRotation = holderNode->Transformation.GetRotation();
			FQuaternion newRot = LerpQuat(currentRotation, FQuaternion(0.707f, 0.0f, 0.0f, 0.707f) * currentRotation, Duration(dt));
			holderNode->Transformation.SetRotation(newRot);
			//end of testing
		}
	}
}