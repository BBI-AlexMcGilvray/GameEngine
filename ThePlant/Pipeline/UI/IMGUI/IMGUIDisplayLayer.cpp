#include "Pipeline/UI/IMGUI/IMGUIDisplayLayer.h"

#include "Pipeline/Dependencies/IMGUI/imgui.h"
#include "Pipeline/Dependencies/IMGUI/backends/imgui_impl_sdl.h"
#include "Pipeline/Dependencies/IMGUI/backends/imgui_impl_opengl3.h"

namespace Application {
namespace UI {
namespace IMGUI {
    IMGUIDisplayLayer::IMGUIDisplayLayer(UI::IMGUI::Manager& imguiManager)
    : _imguiManager(imguiManager)
    {}

    void IMGUIDisplayLayer::Render(Rendering::Renderer& renderer)
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

    void IMGUIDisplayLayer::_RenderManager()
    {
        ImGui::Begin("All Windows");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        // this stuff shouldn't be here, it should be in the specific UIs
        ImGui::BeginMainMenuBar();
        ImGui::Text("Test");
        ImGui::EndMainMenuBar();
        // For the below: we should follow more closely what the imgui_demo does in it's example for more contol
        // we should also split the logic for building the menu bar and the dock frame into different functions (though both can get called from here)
        //  ** is there also a footer? -> no
        // ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

        auto windowLock = _imguiManager.LockWindows();
        const auto& allWindows = _imguiManager.GetAllWindows();

        for (auto& window : allWindows)
        {            
            auto& actualWindow = window.get();

            bool previousDraw = actualWindow.draw;
            ImGui::Checkbox(actualWindow.GetName().c_str(), &(actualWindow.draw));
            if (previousDraw != actualWindow.draw)
            {
                actualWindow.OnDrawChange();
            }
        }

        _imguiManager.UnlockWindows(std::move(windowLock));

        ImGui::End();
    }

    void IMGUIDisplayLayer::_RenderWindows()
    {
        auto windowLock = _imguiManager.LockWindows();
        const auto& allWindows = _imguiManager.GetAllWindows();

        for (auto& window : allWindows)
        {
            auto& actualWindow = window.get();
            
            if (actualWindow.draw)
            {
                ImGui::Begin(actualWindow.GetName().c_str(), &(actualWindow.draw));
                {
                    actualWindow.Draw(); // this means we likely need the ::Draw methods to be const and mutexed to handle any changes in the windows?
                }
                ImGui::End();
            }
        }

        _imguiManager.UnlockWindows(std::move(windowLock));
    }
} // namespace IMGUI
} // namespace UI
} // namespace Rendering