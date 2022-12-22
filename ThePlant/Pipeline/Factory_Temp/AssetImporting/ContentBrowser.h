#pragma once

#include "Pipeline/UI/IMGUI/Window.h"

namespace Editor
{
    /*
    References:
    - https://github.com/gallickgunner/ImGui-Addons
    - https://github.com/ocornut/imgui/issues/2602
        - https://learn.microsoft.com/en-us/windows/win32/api/shellapi/nf-shellapi-dragacceptfiles
        - https://learn.microsoft.com/en-us/windows/win32/api/oleidl/nn-oleidl-idroptarget
    */
    class ContentBrowser : public Application::UI::IMGUI::Window
    {
        void Draw() override;
    };
} // \namespace Editor