#pragma once

#include "Core/Threading/Thread.h"

#include "Pipeline/Headers/SDL2Manager.h"
#include "Pipeline/Input/Headers/InputManager.h"
#include "Pipeline/Rendering/Headers/RenderManager.h"
#include "Pipeline/UI/IMGUI/Manager.h"

#ifdef MULTITHREADED_RENDERING
namespace Application
{
    struct ApplicationManager;
    
namespace Rendering
{
    class RenderThread
    {
    public:
        enum class ExecutionState
        {
            Fresh,
            Set,
            Initialize,
            Start,
            Update,
            End,
            CleanUp
        };

        RenderThread(ApplicationManager& applicationManager);
        ~RenderThread() = default;

        RenderThread(RenderThread&&) = default;
        RenderThread& operator=(RenderThread&&) = default;

        RenderThread(const RenderThread&) = delete;
        RenderThread& operator=(const RenderThread&) = delete;

        void SetThread(Core::Threading::Thread&& thread);
        Core::Threading::Thread& GetThread();
        Core::Threading::Thread ReleaseThread();
        
        void SetExecutionState(ExecutionState executionState);
        ExecutionState GetExecutionState() const;
        ExecutionState GetCompletedState() const;

        void RunThread();

    private:
        Core::Threading::Thread _thread;
        std::atomic<ExecutionState> _executionState;
        std::atomic<ExecutionState> _completedState;

        void _CompleteState(ExecutionState executionState);
    #if DEBUG
        void _VerifyState(ExecutionState executionState) const;
    #endif

        Application::SDL2Manager& _sdl;
        UI::IMGUI::Manager& _imguiUI;
        Input::InputManager& _inputManager;
        Rendering::RenderManager& _renderManager;

        Delegate<> _onQuit;

        void _WaitForDifferentStateThan(ExecutionState state);
        void _WaitForState(ExecutionState state);

        void _Initialize();
        void _Start();
        void _Update();
        void _End();
        void _CleanUp();
    };

    // helper function to kick off the render thread so it doesn't live in RenderManager
    // RenderManager should have a 'Draw' and a 'Render' function (or better names)
    //      - Render -> queue things to render
    //      - Draw -> actually draw
    // this would be in charge of calling the proper initialization methods and such so that everything is initialized to the proper thread
    //      - opengl, imgui, ...
    void CreateAndRunRenderThread(RenderThread& renderThread, Core::Threading::Thread&& thread);
} // namespace Rendering
} // namespace Application
#endif