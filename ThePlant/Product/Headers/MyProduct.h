#pragma once

#include "Materials/Core/Headers/PtrDefs.h"
#include "Materials/Core/Headers/TimeDefs.h"

#include "Pipeline/ECS/DataOriented/IDs.h"

#include "Product/Headers/CameraController.h"
#include "Product/Scripting/LuaManager.h"

// testing
#include "Core/Math/Headers/Vector3.h"
// \testing

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
        Application::Entity _camera;

        CameraController _cameraController;
        LuaManager _luaManager;

        // testing
        Application::Entity _static;
        Application::Entity _animated;

        Application::Entity _collider;
        Application::Entity _trigger;

        bool _dir1;
        Core::Second _swapTime;
        Core::Second _currentSwap;
        Core::Math::Float3 _leftPos;
        Core::Math::Float3 _rightPos;
        // \testing
    };
}