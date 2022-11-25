#include "Pipeline/UI/IMGUI/Manager.h"

#include "Pipeline/UI/IMGUI/Windows/DefaultWindows.h"

#include "Pipeline/Dependencies/IMGUI/imgui.h"
#include "Pipeline/Dependencies/IMGUI/backends/imgui_impl_sdl.h"
#include "Pipeline/Dependencies/IMGUI/backends/imgui_impl_opengl3.h"

namespace Application
{
namespace UI
{  
namespace IMGUI
{
    Manager::Manager(const WindowManager& window, const GLContextManager& glContext)
    : _window(window)
    , _glContext(glContext)
    {}

    void Manager::Initialize()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        // (void)io; // to suppress 'unused variable' errors (not needed if used like in the below)
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    #ifndef MULTITHREADED_RENDERING
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // does not work with multithreaded rendering (maybe we only enable that in non-editor builds?)
    #endif // MULTITHREADED_RENDERING
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        // Setup Platform/Renderer backends
        ImGui_ImplSDL2_InitForOpenGL(_window.GetWindow(), _glContext.GetContext());
        ImGui_ImplOpenGL3_Init(NULL); // see documentation for notes

        RegisterDefaultWindows(*this);
    }

    void Manager::Start()
    {

    }

    void Manager::Render()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        
        _RenderManager();
        
        _RenderWindows();

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // this is to support having multiple viewports via IMGUI
        // Reference: https://github.com/ocornut/imgui/wiki/Multi-Viewports
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
            SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
        }
    }

    void Manager::End()
    {

    }

    void Manager::CleanUp()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }

    void Manager::_RenderManager()
    {
        ImGui::Begin("All Windows");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        
        std::unique_lock<std::mutex> lock(_mutex);
        for (auto& window : _windows)
        {            
            auto& actualWindow = *(window.second);

            bool previousDraw = actualWindow.draw;
            ImGui::Checkbox(actualWindow.GetName().c_str(), &(actualWindow.draw));
            if (previousDraw != actualWindow.draw)
            {
                actualWindow.OnDrawChange();
            }
        }
        lock.unlock();

        ImGui::End();
    }

    void Manager::_RenderWindows()
    {
        std::unique_lock<std::mutex> lock(_mutex);
        for (auto& window : _windows)
        {
            auto& actualWindow = *(window.second);
            
            if (actualWindow.draw)
            {
                ImGui::Begin(actualWindow.GetName().c_str(), &(actualWindow.draw));
                {
                    actualWindow.Draw(); // this means we likely need the ::Draw methods to be const and mutexed to handle any changes in the windows?
                }
                ImGui::End();
            }
        }
    }
}
}
}