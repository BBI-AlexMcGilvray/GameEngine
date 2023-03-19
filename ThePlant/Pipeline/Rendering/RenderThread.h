#pragma once

#include "Core/Threading/Thread.h"

#include "Pipeline/Input/Headers/InputManager.h"
#include "Pipeline/Rendering/Headers/RenderManager.h"
#include "Pipeline/UI/IMGUI/Manager.h"

namespace Application
{
    struct ApplicationManager;
    
namespace Rendering
{
    class RenderThread
    {
    public:
        RenderThread(Input::InputManager& inputManager, Rendering::RenderManager& renderManager);
        ~RenderThread() = default;

        RenderThread(RenderThread&&) = default;
        RenderThread& operator=(RenderThread&&) = default;

        RenderThread(const RenderThread&) = delete;
        RenderThread& operator=(const RenderThread&) = delete;

        bool IsRunning() const;
        void SetThread(Core::Threading::Thread&& thread);
        Core::Threading::Thread& GetThread();
        void StopThread();
        
        void RunThread();

    private:
        Core::Threading::Thread _thread;
        std::atomic<bool> _runThread;
    #if DEBUG
        bool _validThread = false;
        void _SetValidity(bool validity);
        void _VerifyValidity(bool validityShouldBe) const;
    #endif

        Input::InputManager& _inputManager;
        Rendering::RenderManager& _renderManager;
    };

    // helper function to kick off the render thread so it doesn't live in RenderManager
    // RenderManager should have a 'Draw' and a 'Render' function (or better names)
    //      - Render -> queue things to render
    //      - Draw -> actually draw
    // this would be in charge of calling the proper initialization methods and such so that everything is initialized to the proper thread
    //      - opengl, imgui, ...
    void CreateAndRunRenderThread(ApplicationManager& applicationManager, RenderThread& renderThread, Core::Threading::Thread&& thread);
} // namespace Rendering
} // namespace Application