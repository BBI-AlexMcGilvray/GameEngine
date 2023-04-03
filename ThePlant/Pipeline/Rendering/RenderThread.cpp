#include "Pipeline/Rendering/RenderThread.h"

#include "Core/Logging/LogFunctions.h"

#include "Pipeline/Headers/ApplicationManager.h"
#include "Pipeline/Dependencies/IMGUI/backends/imgui_impl_sdl.h"

#ifdef MULTITHREADED_RENDERING
namespace Application
{
namespace Rendering
{
    RenderThread::RenderThread(Input::InputManager& inputManager, Rendering::RenderManager& renderManager)
    : _runThread(false)
    , _inputManager(inputManager)
    , _renderManager(renderManager)
    {}

    bool RenderThread::IsRunning() const
    {
    #if DEBUG
        _VerifyValidity(_runThread);
    #endif
        return _runThread;
    }

    Core::Threading::Thread& RenderThread::GetThread()
    {
    #if DEBUG
        _VerifyValidity(true);
    #endif
        return _thread;
    }

    void RenderThread::SetThread(Core::Threading::Thread&& thread)
    {
    #if DEBUG
        _VerifyValidity(false);
        _SetValidity(true);
    #endif
        _thread = std::move(thread);
    }

    void RenderThread::StopThread()
    {
    #if DEBUG
        _VerifyValidity(true);
    #endif
        _runThread = false;
        _thread.Complete();
    #if DEBUG
        _VerifyValidity(false);
    #endif
    }

    void RenderThread::RunThread()
    {
        _runThread = true;
        while (IsRunning())
        {
            DEBUG_PROFILE_SCOPE("Render Thread"); // this thread is currently locked at 13ms, apparently by sdl's vsync (see above)
            _inputManager.ThreadedUpdate();
            _renderManager.ThreadedRender();
        }
    }

#if DEBUG
    void RenderThread::_SetValidity(bool validity)
    {
        _validThread = validity;
    }

    void RenderThread::_VerifyValidity(bool validityShouldBe) const
    {
        if (_validThread != validityShouldBe)
        {
            CORE_THROW("RenderThread", "Thread validity does not match expectation!");
        }
    }
#endif

    // helper function to kick off the render thread so it doesn't live in RenderManager
    // RenderManager should have a 'Draw' and a 'Render' function (or better names)
    //      - Render -> queue things to render
    //      - Draw -> actually draw
    // this would be in charge of calling the proper initialization methods and such so that everything is initialized to the proper thread
    //      - opengl, imgui, ...
    void CreateAndRunRenderThread(ApplicationManager& applicationManager, RenderThread& renderThread, Core::Threading::Thread&& thread)
    {
        SDL_GL_MakeCurrent(applicationManager.SDLManager().GetWindowManager().GetWindow(), nullptr);

        renderThread.SetThread(std::move(thread));

        renderThread.GetThread().SetTaskAndRun(std::packaged_task<void()>([&applicationManager, &renderThread]
        {
            // should we only initialize opengl/sdl and stuff here?
                // NOTE: if we do (or even regardless), the window size stuff would then need to be threaded
            // initialize IMGUI
            SDL_GL_MakeCurrent(applicationManager.SDLManager().GetWindowManager().GetWindow(), applicationManager.SDLManager().GetContextManager().GetContext());
            applicationManager.IMGUI().Initialize();

            renderThread.RunThread();

            applicationManager.IMGUI().CleanUp();
        }));
    }
} // namespace Rendering
} // namespace Application
#endif