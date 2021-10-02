#include "Product/Headers/MyProduct.h"

// testing
#include "Pipeline/Headers/ApplicationManager.h"
#include "Pipeline/StateSystem/Headers/StateManager.h"

#include "Pipeline/Geometric/Headers/CameraNode.h"
#include "Pipeline/Geometric/Headers/ContentBase.h"
#include "Pipeline/Geometric/Headers/Node.h"

#include "Pipeline/Rendering/Headers/RenderComponent.h"
#include "Pipeline/Rendering/3D/Headers/ModelBase.h"
#include "Pipeline/Rendering/3D/Headers/AnimatedModel.h"

#include "Pipeline/Input/Headers/InputController.h"
#include "Pipeline/Input/Headers/InputManager.h"

#include "Product/Supplies/Assets.h"

#include "Core/Math/Headers/UtilityFunctions.h"
#include "Core/Math/Headers/MatrixFunctions.h"
// \testing

namespace Product
{
    void MyProduct::initialize()
    {
        Application::StateManager& stateManager = Application::ApplicationManager::AppStateManager();
        Application::State& currentState = stateManager.GetActiveState();
        _currentWorld = &(currentState.getHierarchy());

        // before this we need to add a world, then add the camera to it
        // this will be data driven from the future
        _cameraNode = _currentWorld->AddChild<Application::Geometric::CameraNode>(Application::ApplicationManager::AppRenderManager(), 1280.0f / 1080.0f);
        // camera position not acting correctly in final transformation matrix (from camera)
        _cameraNode->Transformation.SetPosition(Float3(0.0f, 0.0f, 20.0f));
        _cameraNode->CameraComponent->GetCamera()->LookAt(Float3(0.0f, 0.0f, 0.0f));

        _cameraController = CameraController(_cameraNode);
        Application::Input::InputManager& inputManager = Application::ApplicationManager::AppInputManager();
        inputManager.setInputController<Application::Input::DefaultInputController>();
        inputManager->addReceiver(&_cameraController);

        _luaManager.initialize();
    }

    void MyProduct::start()
    {
        _luaManager.start();

        //Ptr<Node> staticMeshNode = AddChild<Node>("StaticMesh", Float3(-10.0f, 0.0f, 0.0f));
        //Ptr<ContentBase> staticMeshContent = staticMeshNode->AddContent(MakeUnique<ContentBase>());
        //ComponentPtr<Hierarchy> staticHierarchyComponent = staticMeshContent->GetComponent<Hierarchy>();
        //ComponentPtr<Rendering::Render> staticRenderComponent = staticMeshContent->AddComponent<Rendering::Render>(ApplicationManager::AppRenderManager().GetObjectManagerForState(ParentState));
        //staticRenderComponent->AddRenderObject<Rendering::ModelBase>(&(staticHierarchyComponent->GetHeirarchyNode()->Transformation), Data::Ast.spmdl.MI_0);

        _holderNode = _currentWorld->AddChild<Application::Geometric::Node>("Holder");

        Ptr<Application::Geometric::Node> animatedMeshNode = _holderNode->AddChild<Application::Geometric::Node>("AnimatedMesh", Float3(0.0f, 0.0f, 0.0f), FQuaternion(0.0f, 0.707f, 0.0f, 0.707f) * FQuaternion(-0.707f, 0.0f, 0.0f, 0.707f));
        //animatedMeshNode->Transformation.SetRotation()

        Ptr<Application::Geometric::ContentBase> animatedMeshContent = animatedMeshNode->AddContent<AnimatedModel>(animatedMeshNode, Data::Ast.amdl.Woman_0);
        animatedMeshContent->Initialize();
        //ComponentPtr<Rendering::Render> animatedRenderComponent = animatedMeshContent->AddComponent<Rendering::Render>(ApplicationManager::AppRenderManager().GetObjectManagerForState(ParentState));
        //Ptr<Rendering::AnimatedModel> animatedModel = animatedRenderComponent->SetRenderObject<Rendering::AnimatedModel>(animatedMeshNode, Data::Ast.amdl.Woman_0);
        _neckBone = animatedMeshNode->GetChild("LeftShoulder");// Targetting the "RootNode" works... maybe an issue with how the values are uploaded?
    }

    void MyProduct::update(Core::Second dt)
    {
        _luaManager.update(dt);

        // just for testing currently
        FQuaternion currentRotation = _holderNode->Transformation.GetRotation();
        FQuaternion newRot = Core::Math::LerpQuat(currentRotation, FQuaternion(0.0f, 0.1f, 0.0f, 0.9f) * currentRotation, Duration(dt));
        _holderNode->Transformation.SetRotation(newRot);

        FQuaternion rotationModification = _neckBone->Transformation.GetRotation();
        _neckBone->Transformation.AdjustRotation(FQuaternion(0.0f, 0.0f, 0.01f, 0.99f));
        //end of testing
    }

    void MyProduct::end()
    {
        _luaManager.end();
    }

    void MyProduct::cleanUp()
    {
        _luaManager.cleanUp();
    }
}