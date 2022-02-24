#include "Product/Headers/ProductManager.h"

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
            DEBUG_PROFILE_SCOPE("ProductManager::Update");
            Core::Second dt = _time.Update();
            while (dt > 0_s) {
                _pipeline->Update(dt);
                _myProduct.update(dt);
                dt = _time.GetAccumulatedTime();
            }
            _pipeline->Render(); // rendering takes up over half the frame, threading this would be huge!
            // take a look at Unity's order of execution and work on cleaning up execution order
            //      - https://docs.unity3d.com/Manual/ExecutionOrder.html

            // clear before final pop to not clear the final stack.
            // however, this means that the displayed data is one frame behind
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