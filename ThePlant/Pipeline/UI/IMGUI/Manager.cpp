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
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // see: https://github.com/ocornut/imgui/wiki/Docking
    #ifndef MULTITHREADED_RENDERING
        // NOTE: If we had the rendering logic and the input logic on the same thread (instead of separate like now), then this issue may not exist
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // does not work with multithreaded rendering (maybe we only enable that in non-editor builds?)
    #endif // MULTITHREADED_RENDERING
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        // Setup Platform/Renderer backends
        ImGui_ImplSDL2_InitForOpenGL(_window.GetWindow(), _glContext.GetContext());
        ImGui_ImplOpenGL3_Init(nullptr); // see documentation for notes

        RegisterDefaultWindows(*this);
    }

    void Manager::Start()
    {
        
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
    
    std::vector<std::reference_wrapper<Window>> Manager::GetAllWindows()
    {
        auto lock = LockWindows();

        std::vector<std::reference_wrapper<Window>> windowCollection;
        windowCollection.reserve(_windows.size());

        for (auto& window : _windows)
        {
            windowCollection.push_back(*(window.second));
        }

        // don't need to unlock explicitly as the lock will go out of scope
        return windowCollection;
    }

    std::unique_lock<std::recursive_mutex> Manager::LockWindows()
    {
        return std::unique_lock<std::recursive_mutex>(_mutex);
    }

    void Manager::UnlockWindows(std::unique_lock<std::recursive_mutex>&& lock)
    {
        // since it is an rvalue, we just need to make sure it's lifetime doesn't persist
        (void)(lock);
    }
}
}
}