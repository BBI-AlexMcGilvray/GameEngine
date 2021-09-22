#pragma once

#include "Core/Headers/PtrDefs.h"

#include "Pipeline/Headers/ApplicationManager.h"

// will be what sets up the initial state of the world

/*
Options:
- Override application manager that will create an initial state
- Create state with default name that will be opened
    - then follows data
- No default application manager, instead just one that handles creating the default state

Notes:
- Work on this now
- Remove the debug work in Pipeline to test functionality and have it be in this test project
- Register InputController
- Register testing InputReceiver
    - Have this move the camera (for now) to test
- Side note: Get the 'DEBUG' config to actually define DEBUG (or _DEBUG, or whatever we are using)
*/

namespace Product
{
    class ProductManager
    {
    public:
        void run();

    private:
        Core::Ptr<Application::ApplicationManager> _pipeline;
        FixedStepTimeManager _time;

        bool _initialize();
        void _start();
        void _update();
        void _end();
        void _cleanUp();
    };
}