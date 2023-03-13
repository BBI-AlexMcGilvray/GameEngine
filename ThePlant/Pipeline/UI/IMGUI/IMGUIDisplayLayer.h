#pragma once

#include "Pipeline/Rendering/Display.h"
#include "Pipeline/UI/IMGUI/Manager.h"

namespace Application {
namespace UI {
namespace IMGUI {
  class IMGUIDisplayLayer : public Rendering::IDisplayLayer
  {
    public:
        IMGUIDisplayLayer(UI::IMGUI::Manager& imguiManager);

        virtual void Render(Rendering::Renderer& renderer) override;

    private:
        UI::IMGUI::Manager& _imguiManager;

        void _RenderManager();
        void _RenderWindows();
  };
} // namespace IMGUI
} // namespace UI
} // namespace Rendering