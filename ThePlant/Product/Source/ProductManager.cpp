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
        _myProduct.initialize();

        return pipelineInitialized;
    }

    void ProductManager::_start()
    {
        _pipeline.Start();
        _myProduct.start();

        // for now, this is where we can put in test code
    }

    void ProductManager::_update()
    {
        Application::Time::TimeSystem& timeSystem = _pipeline.TimeSystem();
        timeSystem.Initialize(); // HACK: need to do this here due to first frame being too long
        
        // take a look at Unity's order of execution and work on cleaning up execution order
        //      - https://docs.unity3d.com/Manual/ExecutionOrder.html
        while (!_pipeline.quit())
        {
            DEBUG_PROFILE_SCOPE("ProductManager::Update");
            timeSystem.Update();
            while (timeSystem.TakeFixedStep() && !_pipeline.quit()) { // checking quit here as well to enforce responsiveness (otherwise we don't quit until timesteps are caught up)
                Core::Second dt = timeSystem.GetDeltaTime();
                _pipeline.Update(dt);
                _myProduct.update(dt);
            // #ifdef MULTITHREADED_RENDERING // NOTE: not actually used due to current location of define
                _pipeline.Render(); // when threaded, this pushes the current buffer to the next thread, if we only did it once we would duplicate render data per frame
            // #endif
            }
        // #ifndef MULTITHREADED_RENDERING // NOTE: not actually used due to current location of define - need to fix, bottom should NOT be commented
            // _pipeline.Render(); // if rendering is not threaded, then we only render once per frame (otherwise waste time)
        // #endif
        }
    }

    void ProductManager::_end()
    {
        _myProduct.end();
        _pipeline.End();   
    }

    void ProductManager::_cleanUp()
    {
        _myProduct.cleanUp();
        _pipeline.CleanUp();
    }
}