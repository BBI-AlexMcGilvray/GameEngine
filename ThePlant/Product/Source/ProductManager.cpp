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
        _pipeline = Application::ApplicationManager::Application();

        bool pipelineInitialized = _pipeline->Initialize();
        _time.Initialize();

        return pipelineInitialized;
    }

    void ProductManager::_start()
    {
        _pipeline->Start();
        _time.Start();

        // for now, this is where we can put in test code
    }

    void ProductManager::_update()
    {
        while (!_pipeline->quit())
        {
            _pipeline->Update();

            Core::Second dt = _time.Update();
            while (dt > 0_s) {
                _pipeline->Update(dt);
                dt = _time.GetAccumulatedTime();
            }
        }
    }

    void ProductManager::_end()
    {
        _pipeline->End();
        _time.End();
    }

    void ProductManager::_cleanUp()
    {
        _pipeline->CleanUp();
        _time.CleanUp();
    }
}