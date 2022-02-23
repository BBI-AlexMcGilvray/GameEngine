#pragma once

#include "Pipeline/StateSystem/Headers/State.h"

#include "Pipeline/ECS/DataOriented/IDs.h"

#include "Product/Headers/CameraController.h"

// testing
#include "Core/Math/Headers/Vector3.h"
// \testing

namespace Application
{
    struct ApplicationManager;
}

namespace Product
{
struct MyState : public Application::State
{
    MyState(Application::ApplicationManager& applicationManager);

    void Initialize() override;
    void Start() override;
    void End() override;
    void CleanUp() override;

private:
    Application::Entity _camera;

    CameraController _cameraController;

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

    void _PreECSUpdate(Second dt) override;
    void _PostECSUpdate(Second dt) override;
};
}