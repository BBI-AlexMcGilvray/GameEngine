#include "Pipeline/Rendering/RenderThread.h"

#include "Core/Logging/LogFunctions.h"

#include "Pipeline/Headers/ApplicationManager.h"
#include "Pipeline/Dependencies/IMGUI/backends/imgui_impl_sdl.h"

#ifdef MULTITHREADED_RENDERING
namespace Application
{
namespace Rendering
{
    RenderThread::RenderThread(ApplicationManager& applicationManager)
    : _executionState(ExecutionState::Fresh)
    , _completedState(ExecutionState::Fresh)
    , _sdl(applicationManager.SDLManager())
    , _imguiUI(applicationManager.IMGUI())
    , _inputManager(applicationManager.InputManager())
    , _renderManager(applicationManager.RenderManager())
    , _onQuit([&applicationManager]() {
            applicationManager.Quit();
            return false;
        }, _inputManager.Quit)
    {}

    void RenderThread::SetThread(Core::Threading::Thread&& thread)
    {
    #if DEBUG
        _VerifyState(ExecutionState::Fresh);
    #endif
        SetExecutionState(ExecutionState::Set);
        _CompleteState(ExecutionState::Set);
        _thread = std::move(thread);
    }

    Core::Threading::Thread& RenderThread::GetThread()
    {
        // wait for this thread to be complete before returning
        _WaitForDifferentStateThan(ExecutionState::Fresh);
        return _thread;
    }

    Core::Threading::Thread RenderThread::ReleaseThread()
    {
        _WaitForState(ExecutionState::Fresh);
        return std::move(_thread);
    }
    
    void RenderThread::SetExecutionState(RenderThread::ExecutionState executionState)
    {
    #if DEBUG
        _VerifyState(_executionState); // make sure we've finished the current state
    #endif
        _executionState = executionState;
    #if DEBUG
        _VerifyState(_executionState); // make sure the new state is 'forward'
    #endif
    }

    RenderThread::ExecutionState RenderThread::GetExecutionState() const
    {
    #if DEBUG
        _VerifyState(_executionState);
    #endif
        return _executionState;
    }

    RenderThread::ExecutionState RenderThread::GetCompletedState() const
    {
        return _completedState;
    }

    void RenderThread::RunThread()
    {
        // how do we wait for the state to be changed to step through?

        while (true)
        {
        #if DEBUG
            _VerifyState(_executionState);
        #endif

            switch(_executionState)
            {
                case ExecutionState::Initialize:
                {
                    _Initialize();
                    _WaitForDifferentStateThan(ExecutionState::Initialize);
                    break;
                }
                case ExecutionState::Start:
                {
                    _Start();
                    _WaitForDifferentStateThan(ExecutionState::Start);
                    break;
                }
                case ExecutionState::Update:
                {
                    _Update();
                    break;
                }
                case ExecutionState::End:
                {
                    _End();
                    _WaitForDifferentStateThan(ExecutionState::End);
                    break;
                }
                case ExecutionState::CleanUp:
                {
                    _CleanUp();
                    _WaitForDifferentStateThan(ExecutionState::CleanUp);
                    return; // once we're done cleaning up, end thread loop
                }
            }
        }

        #if DEBUG
            _VerifyState(ExecutionState::Fresh);
        #endif
    }

    void RenderThread::_CompleteState(ExecutionState executionState)
    {
        _completedState = executionState;
    }

#if DEBUG
    void RenderThread::_VerifyState(ExecutionState executionState) const
    {
        if (_completedState > executionState)
        {
            CORE_THROW("RenderThread", "Thread execution state has already completed!");
        }
    }
#endif

    void RenderThread::_WaitForDifferentStateThan(ExecutionState state)
    {
        while (_executionState == state)
        {}
    }

    void RenderThread::_WaitForState(ExecutionState state)
    {
        while (_executionState != state)
        {}
    }

    void RenderThread::_Initialize()
    {
        // sdl only needs the render manager for initialization, we can change that initialize call
        if (!_sdl.Initialize(_renderManager)) // do we also store the application manager in here? how else would we call this (can sdl be created with the required info?)
        {
            return;
        }
        _imguiUI.Initialize();
        _inputManager.initialize();
        _renderManager.Initialize(_sdl, _inputManager);

        _CompleteState(ExecutionState::Initialize);
    }

    void RenderThread::_Start()
    {
        _renderManager.Start();
        _inputManager.start();
        _imguiUI.Start();
        _sdl.Start();

        _CompleteState(ExecutionState::Start);
    }

    void RenderThread::_Update()
    {
        DEBUG_PROFILE_SCOPE("Render Thread"); // this thread is currently locked at 13ms, apparently by sdl's vsync (see above)
        _inputManager.ThreadedUpdate();
        _renderManager.ThreadedRender();

        _CompleteState(ExecutionState::Update);
    }

    void RenderThread::_End()
    {
        _renderManager.End();
        _inputManager.end();
        _imguiUI.End();
        _sdl.End();

        _CompleteState(ExecutionState::End);
    }

    void RenderThread::_CleanUp()
    {
        _renderManager.CleanUp();
        _inputManager.cleanUp();
        _imguiUI.CleanUp();
        _sdl.CleanUp();

        _CompleteState(ExecutionState::CleanUp);
        SetExecutionState(ExecutionState::Fresh);
    }

    // helper function to kick off the render thread so it doesn't live in RenderManager
    // RenderManager should have a 'Draw' and a 'Render' function (or better names)
    //      - Render -> queue things to render
    //      - Draw -> actually draw
    void CreateAndRunRenderThread(RenderThread& renderThread, Core::Threading::Thread&& thread)
    {
        renderThread.SetThread(std::move(thread));

        renderThread.GetThread().SetTaskAndRun(std::packaged_task<void()>([&renderThread]
        {
            renderThread.RunThread();
        }));
    }
} // namespace Rendering
} // namespace Application
#endif