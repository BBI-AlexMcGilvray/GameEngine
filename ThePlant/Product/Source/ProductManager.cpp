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
            _pipeline->Update();

            Core::Second dt = _time.Update();
            while (dt > 0_s) {
                _myProduct.update(dt);
                _pipeline->Update(dt);
                dt = _time.GetAccumulatedTime();
            }
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