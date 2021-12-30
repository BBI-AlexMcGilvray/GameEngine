#pragma once

#include "Materials/Core/Headers/PtrDefs.h"
#include "Materials/Core/Headers/TimeDefs.h"

#include "Pipeline/ECS/DataOriented/IDs.h"

#include "Product/Headers/CameraController.h"
#include "Product/Scripting/LuaManager.h"

/*
Notes:
- Work on this now
- Remove the debug work in Pipeline to test functionality and have it be in this test project
- Register InputController
- Register testing InputReceiver
    - Have this move the camera (for now) to test
- Side note: Get the 'DEBUG' config to actually define DEBUG (or _DEBUG, or whatever we are using)
*/

namespace Application::Geometric
{
    struct Node;
    struct World;
    struct CameraNode;
}

namespace Product
{
    class MyProduct
    {
    public:
        void initialize();
        void start();
        void update(Core::Second dt);
        void end();
        void cleanUp();

    private:
        // Core::Ptr<Application::Geometric::Node> _holderNode;
        // Core::Ptr<Application::Geometric::Node> _shoulderBone;
        Application::Entity _camera;

        CameraController _cameraController;
        LuaManager _luaManager;

        // testing
        Application::Entity _entity;
        // \testing
    };
}