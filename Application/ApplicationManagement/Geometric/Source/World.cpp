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
			cameraNode->Transformation.SetPosition(Float3(20.0f, 0.0f, 0.0f));
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

			holderNode = AddChild<Node>("Holder", Float3(0.0f, 0.0f, 5.0f));

			Ptr<Node> animatedMeshNode = holderNode->AddChild<Node>("AnimatedMesh", Float3(0.0f, 0.0f, 5.0f));
			Ptr<ContentBase> animatedMeshContent = animatedMeshNode->AddContent(MakeUnique<ContentBase>());
			ComponentPtr<Rendering::Render> animatedRenderComponent = animatedMeshContent->AddComponent<Rendering::Render>(ApplicationManager::AppRenderManager().GetObjectManagerForState(ParentState));
			animatedRenderComponent->AddRenderObject<Rendering::AnimatedModel>(animatedMeshNode, Data::Ast.amdl.Woman_0);
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
			FQuaternion newRot = LerpQuat(holderNode->Transformation.GetRotation(), FQuaternion(0.525322f, 0.8509035f, 0.0f, 0.0f) * holderNode->Transformation.GetRotation(), Duration(dt));
			holderNode->Transformation.SetRotation(newRot);
		}
	}
}