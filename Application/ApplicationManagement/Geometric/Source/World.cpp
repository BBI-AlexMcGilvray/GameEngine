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

			//Ptr<Node> staticMeshNode = AddChild<Node>("StaticMesh", Float3(-10.0f, 0.0f, 0.0f));
			//Ptr<ContentBase> staticMeshContent = staticMeshNode->AddContent(MakeUnique<ContentBase>());
			//ComponentPtr<Hierarchy> staticHierarchyComponent = staticMeshContent->GetComponent<Hierarchy>();
			//ComponentPtr<Rendering::Render> staticRenderComponent = staticMeshContent->AddComponent<Rendering::Render>(ApplicationManager::AppRenderManager().GetObjectManagerForState(ParentState));
			//staticRenderComponent->AddRenderObject<Rendering::ModelBase>(&(staticHierarchyComponent->GetHeirarchyNode()->Transformation), Data::Ast.spmdl.MI_0);

			holderNode = AddChild<Node>("Holder");

			Ptr<Node> animatedMeshNode = holderNode->AddChild<Node>("AnimatedMesh", Float3(0.0f, 0.0f, 0.0f), FQuaternion(0.707f, 0.0f, 0.707f, 0.0f) * FQuaternion(0.707f, -0.707f, 0.0f, 0.0f));
			//animatedMeshNode->Transformation.SetRotation()

			Ptr<ContentBase> animatedMeshContent = animatedMeshNode->AddContent(MakeUnique<AnimatedModel>(&(ApplicationManager::AppRenderManager()), animatedMeshNode, Data::Ast.amdl.Woman_0));
			//ComponentPtr<Rendering::Render> animatedRenderComponent = animatedMeshContent->AddComponent<Rendering::Render>(ApplicationManager::AppRenderManager().GetObjectManagerForState(ParentState));
			//Ptr<Rendering::AnimatedModel> animatedModel = animatedRenderComponent->SetRenderObject<Rendering::AnimatedModel>(animatedMeshNode, Data::Ast.amdl.Woman_0);
			neckBone = animatedMeshNode->GetChild("LeftShoulder"); // Targetting the "RootNode" works... maybe an issue with how the values are uploaded?
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

			renderComponent->SetRenderObject<Rendering::SphereRenderObject>(&(hierarchyComponent->GetHeirarchyNode()->Transformation), BLACK, 0.5f);
#endif
		}

		// debugging
		void World::Update(Second dt)
		{
			// just for testing currently
			FQuaternion currentRotation = holderNode->Transformation.GetRotation();
			FQuaternion newRot = LerpQuat(currentRotation, FQuaternion(0.9f, 0.0f, 0.1f, 0.0f) * currentRotation, Duration(dt));
			//holderNode->Transformation.SetRotation(newRot);

			FQuaternion rotationModification = neckBone->Transformation.GetRotation();
			neckBone->Transformation.AdjustRotation(FQuaternion(0.99f, 0.0f, 0.0f, 0.01f));
			//end of testing
		}
	}
}