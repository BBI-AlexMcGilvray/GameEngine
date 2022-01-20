#include "Product/Headers/ProductManager.h"

#include "Pipeline/ECSSystems/AnimationSystem.h"
#include "Pipeline/ECSSystems/CameraSystem.h"
#include "Pipeline/ECSSystems/CollisionSystem.h"
#include "Pipeline/ECSSystems/TransformSystem.h"
#include "Pipeline/ECSSystems/RenderingSystem.h"
#if DEBUG
#include "Pipeline/ECSSystems/DebugSystems/DebugBoneSystem.h"
#include "Pipeline/ECSSystems/DebugSystems/DebugCollisionSystem.h"
#include "Pipeline/ECSSystems/DebugSystems/DebugOctTreeSystem.h"
#include "Pipeline/ECSSystems/DebugSystems/DebugTransformSystem.h"
#endif

namespace Product
{
    void ProductManager::run()
    {
        if (!_initialize()) {
            std::cout << "Failed to initialize application" << std::endl;
            return;
        }

        _start();

        _update();

        _end();
        _cleanUp();
    }

    bool ProductManager::_initialize()
    {
        // the creation of the Application should include the application name, default window size, ...
        // maybe window info should just be a struct (camera?) - tbd
        _pipeline = Application::ApplicationManager::Application();

        bool pipelineInitialized = _pipeline->Initialize();
        _time.Initialize();
        _myProduct.initialize();

        auto sdlManager = _pipeline->AppSDLManager();
        _debugUI = Core::MakeUnique<Application::UI::IMGUIManager>(sdlManager.GetWindowManager(), sdlManager.GetContextManager());
        _debugUI->initialize();

        // the below should probably be a part of the application's initialization (for the default systems at least)
        _pipeline->AppECS().AddSystem<Application::AnimationSystem>(Application::ApplicationManager::AppAnimationManager());
        _pipeline->AppECS().AddSystem<Application::TransformSystem>().AddDependency<Application::AnimationSystem>();
        _pipeline->AppECS().AddSystem<Application::CollisionSystem>(_pipeline->AppCollisionManager()).AddDependency<Application::TransformSystem>();
    #if DEBUG
        _pipeline->AppECS().AddSystem<Application::DebugBoneSystem>(Application::ApplicationManager::AppRenderManager(), Application::ApplicationManager::AppShaderManager()).AddDependency<Application::TransformSystem>();
        _pipeline->AppECS().AddSystem<Application::DebugTransformSystem>(Application::ApplicationManager::AppRenderManager(), Application::ApplicationManager::AppShaderManager()).AddDependency<Application::TransformSystem>();
        _pipeline->AppECS().AddSystem<Application::DebugOctTreeSystem>(Application::ApplicationManager::AppCollisionManager(), Application::ApplicationManager::AppRenderManager(), Application::ApplicationManager::AppShaderManager()).AddDependency<Application::CollisionSystem>();
        _pipeline->AppECS().AddSystem<Application::DebugCollisionSystem>(Application::ApplicationManager::AppCollisionManager(), Application::ApplicationManager::AppRenderManager(), Application::ApplicationManager::AppShaderManager()).AddDependency<Application::CollisionSystem>();
    #endif
        _pipeline->AppECS().AddSystem<Application::CameraSystem>(Application::ApplicationManager::AppRenderManager().GetCameraManager()).AddDependency<Application::TransformSystem>();
        auto& renderingSystem = _pipeline->AppECS().AddSystem<Application::RenderingSystem>(Application::ApplicationManager::AppRenderManager()).AddDependencies<Application::TransformSystem, Application::CameraSystem, Application::AnimationSystem>();
    #if DEBUG
        renderingSystem.AddDependencies<Application::DebugBoneSystem, Application::DebugTransformSystem>();
    #endif

        return pipelineInitialized;
    }

    void ProductManager::_start()
    {
        _pipeline->Start();
        _time.Start();
        _myProduct.start();
        _debugUI->start();

        // for now, this is where we can put in test code
    }

    void ProductManager::_update()
    {
        while (!_pipeline->quit())
        {
            _pipeline->Update();

            Core::Second dt = _time.Update();
            while (dt > 0_s) {
                _myProduct.update(dt);
                _pipeline->Update(dt);
                dt = _time.GetAccumulatedTime();
            }
            // problem is this needs to be called in the middle of rendering (UI should be a second pass after rendering world data)
            //      - this is because of when buffers are cleared and when buffers are switched
            // take a look at Unity's order of execution and work on cleaning that up
            //      - https://docs.unity3d.com/Manual/ExecutionOrder.html
            // _debugUI->update(); // THIS IS WHAT CAUSES RENDERING ISSUES (unsure why exactly)
        }
    }

    void ProductManager::_end()
    {
        _debugUI->end();
        _myProduct.end();
        _time.End();
        _pipeline->End();   
    }

    void ProductManager::_cleanUp()
    {
        _debugUI->cleanUp();
        _myProduct.cleanUp();
        _time.CleanUp();
        _pipeline->CleanUp();
    }
}