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
    Application::EntityId _camera;

    CameraController _cameraController;

    // testing
    Application::EntityId _static;
    Application::EntityId _animated;

    Application::EntityId _collider;
    Application::EntityId _trigger;

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