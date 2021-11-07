#pragma once

#include <map>

#include "Pipeline\Headers\GLContextManager.h"
#include "Pipeline\Headers\WindowManager.h"

#include "Pipeline/Rendering/Headers/CameraManager.h"
#include "Pipeline/Rendering/Headers/MaterialManager.h"
#include "Pipeline/Rendering/Headers/RenderObjectManager.h"
#include "Pipeline/Rendering/Headers/Renderer.h"
#include "Pipeline/Rendering/Headers/Camera.h"
#include "Pipeline/Rendering/Shaders/Headers/ShaderManager.h"

#include "Core/Functionality/Headers/Subscription.h"

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

#include "Core/Math/Headers/Vector4.h"
#include "Core/Math/Headers/Color.h"

namespace Application {
struct State;

namespace Rendering {
  struct RenderManager
  {
    ShaderManager ObjectShaderManager;
    Renderer ObjectRenderer;

    // should subscribe to StateManager::StateChanged to change active state automatically
    RenderManager();

    void Initialize(WindowManager &window, Core::Math::Color clearColor = Core::Math::Color(1.0f, 0.5f, 0.5f, 1.0f));
    void Start();

    void AttachRenderObjectManager(Core::Ptr<State> state, Core::Ptr<RenderObjectManager> objectManager);
    void DettachRenderObjectManager(Core::Ptr<State> state);

    void AttachMaterialManager(Core::Ptr<State> state, Core::Ptr<MaterialManager> materialManager);
    void DettachMaterialManager(Core::Ptr<State> state);

    void AttachCameraManager(Core::Ptr<State> state, Core::Ptr<CameraManager> cameraManager);
    void DettachCameraManager(Core::Ptr<State> state);

    Core::Ptr<State> GetActiveState();
    void SetActiveState(Core::Ptr<State> state);
    void DeactivateState(Core::Ptr<State> state);

    Core::Ptr<RenderObjectManager> GetObjectManagerForState(Core::Ptr<State> state);
    Core::Ptr<MaterialManager> GetMaterialManagerForState(Core::Ptr<State> state);
    Core::Ptr<CameraManager> GetCameraManagerForState(Core::Ptr<State> state);

    void Update(Core::Second dt);
    void Render();

    void End();
    void CleanUp();

    void SetOpenGLAttributes();
#if DEBUG
    void VerifyOpenGLAttributes();
#endif

    Core::Ptr<const Camera> GetCamera() const;

  private:
    Core::Ptr<Camera> RenderCamera = nullptr;
    Core::Math::Color InitialColor;

    Core::Math::Color ClearColor;
    Core::Ptr<WindowManager> Window;

    // should all of these maps be combined into a single object to have a single mapping instead of multiple?
    std::map<Core::Ptr<State>, Core::Ptr<RenderObjectManager>> ObjectManagers;
    std::map<Core::Ptr<State>, Core::Ptr<MaterialManager>> MaterialManagers;
    std::map<Core::Ptr<State>, Core::Ptr<CameraManager>> CameraManagers;
    Core::Ptr<State> ActiveState = nullptr;

    void RenderStart();
    void RenderMiddle();
    void RenderEnd();
  };
}// namespace Rendering
}// namespace Application
