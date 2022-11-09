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
        (void)io; // to suppress 'unused variable' errors (not needed if used like in the below)
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
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
        glViewport(0, 0, _window.Width, _window.Height);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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
        ImGui::End();
    }

    void Manager::_RenderWindows()
    {
        for (auto& window : _windows)
        {
            auto& actualWindow = *(window.second);
            
            if (actualWindow.draw)
            {
                ImGui::Begin(actualWindow.GetName().c_str(), &(actualWindow.draw));
                {
                    actualWindow.Draw();
                }
                ImGui::End();
            }
        }
    }
}
}
}