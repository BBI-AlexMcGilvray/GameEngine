#include "Product/Headers/ProductManager.h"

namespace Product
{
    ProductManager::ProductManager()
    : _myProduct(_pipeline)
    {}

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
        bool pipelineInitialized = _pipeline.Initialize();
        _time.Initialize();
        _myProduct.initialize();

        return pipelineInitialized;
    }

    void ProductManager::_start()
    {
        _pipeline.Start();
        _time.Start();
        _myProduct.start();

        // for now, this is where we can put in test code
    }

    void ProductManager::_update()
    {
        while (!_pipeline.quit())
        {
            DEBUG_PROFILE_SCOPE("ProductManager::Update");
            Core::Second dt = _time.Update();
            while (dt > 0_s) {
                _pipeline.Update(dt);
                _myProduct.update(dt);
                dt = _time.GetAccumulatedTime();
            }
            _pipeline.Render(); // rendering takes up over half the frame, threading this would be huge!
            // take a look at Unity's order of execution and work on cleaning up execution order
            //      - https://docs.unity3d.com/Manual/ExecutionOrder.html
        }
    }

    void ProductManager::_end()
    {
        _myProduct.end();
        _time.End();
        _pipeline.End();   
    }

    void ProductManager::_cleanUp()
    {
        _myProduct.cleanUp();
        _time.CleanUp();
        _pipeline.CleanUp();
    }
}