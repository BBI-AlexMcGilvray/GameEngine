#pragma once

#include <atomic>
#include <map>

#include "Core/Functionality/Headers/Subscription.h"
#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"
#include "Core/Math/Headers/Vector4.h"
#include "Core/Math/Headers/Color.h"
#include "Core/Threading/SafeTypes/TripleBuffer.h"

#include "Pipeline/Headers/GLContextManager.h"
#include "Pipeline/Headers/SDL2Manager.h"
#include "Pipeline/Headers/WindowManager.h"
#include "Pipeline/Input/Headers/InputManager.h"

#include "Pipeline/Rendering/DisplayManager.h"
#include "Pipeline/Rendering/Headers/CameraManager.h"
#include "Pipeline/Rendering/Headers/MaterialManager.h"
#include "Pipeline/Rendering/Headers/Camera.h"
#include "Pipeline/Rendering/Headers/CameraManager.h"
#include "Pipeline/Rendering/Headers/RenderCamera.h"
#include "Pipeline/Rendering/RenderContext.h"
#include "Pipeline/Rendering/RenderFrame.h"
#include "Pipeline/Rendering/Renderer.h"
#include "Pipeline/Rendering/MeshManager.h"

namespace Application {
namespace Rendering {
  struct RenderManager
  {
    RenderManager(ShaderManager& shaderManager, MeshManager& meshManager);

    CameraManager& GetCameraManager();

    void Initialize(SDL2Manager& sdlManager, Input::InputManager& inputManager, Core::Math::Color clearColor = Core::Math::Color(1.0f, 0.5f, 0.5f, 1.0f));
    void Start();

    template <typename DISPLAY_LAYER, typename ...ARGS>
    Core::instanceId<IDisplayLayer> AddDisplay(ARGS&& ...args)
    {
      return _displayManager.AddDisplay<DISPLAY_LAYER>(std::forward<ARGS>(args)...);
    }

    void RemoveDisplay(Core::instanceId<IDisplayLayer> displayId)
    {
      return _displayManager.RemoveDisplay(displayId);
    }

    // for this and the RemoveLayer function, will this support dynamically adding/removing more during runtime? (i.e. not just initialization)
    template <typename LAYER>
    LAYER& AddLayer()
    {
      return _mainThreadRenderFrame.AddLayer<LAYER>();
    }

    template <typename LAYER>
    void RemoveLayer()
    {
      _mainThreadRenderFrame.RemoveLayer<LAYER>();        
    }

    void QueueCamera(RenderCamera&& camera);

    template <typename LAYER>
    void QueueRender(const Context& context)
    {
      SCOPED_MEMORY_CATEGORY("Rendering");
      _mainThreadRenderFrame.QueueRender<LAYER>(context);
    }

    template <typename LAYER>
    void QueueRender(const SkinnedContext& context)
    {
      SCOPED_MEMORY_CATEGORY("Rendering");
      _mainThreadRenderFrame.QueueRender<LAYER>(context);
    }

#ifdef MULTITHREADED_RENDERING
    void ThreadedRender();
#endif
    void Render();

    void End();
    void CleanUp();

    // must be called BEFORE openGL context is created
    void SetOpenGLAttributes();
#if DEBUG
    void VerifyOpenGLAttributes();
#endif
    // must be called AFTER openGL context is created
    void SetOpenGLState();

  private:
    Core::Math::Color _initialColor;

    Core::Math::Color _clearColor;
    Core::Ptr<SDL2Manager> _sdlManager;
    Core::Ptr<Input::InputManager> _inputManager;

    CameraManager _cameraManager;

    void _RenderStart();
    void _RenderMiddle();
    void _RenderEnd();
  
    RenderFrame _mainThreadRenderFrame; // this is the frame we update before we pass it in to the triple buffer
    Core::Threading::TripleBuffer<RenderFrame> _renderFrames;

    DisplayManager _displayManager;

    Renderer _Renderer;

    /*
    NOTES:
      * If we allow for the removal of shaders, we will need to make sure it is thread-safe (since rendering is on a different thread)
      * If that is the case, we either want them to be held here with a way to forward removal (like the displays)
      * OR, we want to have the rendering thread have some way to lock the shaders 
          * it would need to also verify that none of the contexts use any removed shaders
      
      ** The above also applies to meshes! (really anything that is used by render logic)
          ** Meshes aren't ever deleted at the moment! definitely would need a manager

      ** We need a way to tell opengl that is needs to run certain logic to create GLObjects
          * ex: shaders, meshes, ...
          * ideally we can also have a 'load' method to do this stuff in (or just use the Start function in states)
            * should probably be a different method that is called by the State base class to make overriding easier?
          * RenderStart could then call these functions so they are generated as part of the render thread
    */
  };
}// namespace Rendering
}// namespace Application
