#include "Product/Headers/ProductManager.h"

#include "Pipeline/ECSSystems/AnimationSystem.h"
#include "Pipeline/ECSSystems/CameraSystem.h"
#include "Pipeline/ECSSystems/CollisionSystem.h"
#include "Pipeline/ECSSystems/TransformSystem.h"
#include "Pipeline/ECSSystems/RenderingSystem.h"
#if DEBUG
#include "Pipeline/Debugging/Profiling/Utils.h"
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

        // the below should probably be a part of the application's initialization (for the default systems at least)
        _pipeline->AppECS().AddSystem<Application::AnimationSystem>(Application::ApplicationManager::AppAnimationManager());
        _pipeline->AppECS().AddSystem<Application::TransformSystem>().AddDependency<Application::AnimationSystem>();
        _pipeline->AppECS().AddSystem<Application::CollisionSystem>(_pipeline->AppCollisionManager()).AddDependency<Application::TransformSystem>();
    #if DEBUG
        _pipeline->AppECS().AddSystem<Application::DebugBoneSystem>(Application::ApplicationManager::AppRenderManager(), Application::ApplicationManager::AppShaderManager()).AddDependency<Application::TransformSystem>();
        _pipeline->AppECS().AddSystem<Application::DebugTransformSystem>(Application::ApplicationManager::AppRenderManager(), Application::ApplicationManager::AppShaderManager()).AddDependency<Application::TransformSystem>();
        _pipeline->AppECS().AddSystem<Application::DebugOctTreeSystem>(Application::ApplicationManager::AppCollisionManager(), Application::ApplicationManager::AppRenderManager(), Application::ApplicationManager::AppShaderManager()).AddDependencies<Application::TransformSystem, Application::CollisionSystem>();
        _pipeline->AppECS().AddSystem<Application::DebugCollisionSystem>(Application::ApplicationManager::AppCollisionManager(), Application::ApplicationManager::AppRenderManager(), Application::ApplicationManager::AppShaderManager()).AddDependencies<Application::TransformSystem, Application::CollisionSystem>();
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

        // for now, this is where we can put in test code
    }

    void ProductManager::_update()
    {
        while (!_pipeline->quit())
        {
            DEBUG_PROFILE_PUSH("Non-Delta-Time Update");
            _pipeline->Update();
            DEBUG_PROFILE_POP("Non-Delta-Time Update");

            Core::Second dt = _time.Update();
            while (dt > 0_s) {
                DEBUG_PROFILE_PUSH("Product-Delta-Time Update");
                _myProduct.update(dt);
                DEBUG_PROFILE_POP("Product-Delta-Time Update");
                _pipeline->Update(dt);
                dt = _time.GetAccumulatedTime();
            }
            // take a look at Unity's order of execution and work on cleaning up execution order
            //      - https://docs.unity3d.com/Manual/ExecutionOrder.html

            DEBUG_CLEAR_PROFILE();
        }
    }

    void ProductManager::_end()
    {
        _myProduct.end();
        _time.End();
        _pipeline->End();   
    }

    void ProductManager::_cleanUp()
    {
        _myProduct.cleanUp();
        _time.CleanUp();
        _pipeline->CleanUp();
    }
}