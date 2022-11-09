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
            // NOTE: the physics step is too expensive at the moment to do everything in 60 (or 30) fps
            // we either need to lift the cap (which causes the below to break as 'TakeFixedStep' always returns false)
            // or we need to differentiate between capped and uncapped systems (though that won't help at the moment due to the main cost being a fixed step...)
            // threading the different systems may help? unsure
            // ** the above also applied to ApplicationManager::Run
            while (timeSystem.TakeFixedStep() && !_pipeline.quit()) { // checking quit here as well to enforce responsiveness (otherwise we don't quit until timesteps are caught up)
                Core::Second dt = timeSystem.GetDeltaTime();
                _pipeline.Update(dt);
                _myProduct.update(dt);
            #ifdef MULTITHREADED_RENDERING
                _pipeline.Render(); // when threaded, this pushes the current buffer to the next thread, if we only did it once we would duplicate render data per frame
            #endif
            }
        #ifndef MULTITHREADED_RENDERING
            _pipeline.Render(); // if rendering is not threaded, then we only render once per frame (otherwise waste time)
        #endif
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