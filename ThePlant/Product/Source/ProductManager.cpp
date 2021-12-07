#include "Product/Headers/ProductManager.h"

#include "Pipeline/ECSSystems/TransformSystem.h"
#include "Pipeline/ECSSystems/RenderingSystem.h"

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
        _pipeline->AppECS().AddSystem<Application::TransformSystem>();
        _pipeline->AppECS().AddSystem<Application::RenderingSystem>().AddDependency<Application::TransformSystem>();

        bool pipelineInitialized = _pipeline->Initialize();
        _time.Initialize();
        _myProduct.initialize();

        auto sdlManager = _pipeline->AppSDLManager();
        _debugUI = Core::MakeUnique<Application::UI::IMGUIManager>(sdlManager.GetWindowManager(), sdlManager.GetContextManager());
        _debugUI->initialize();

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