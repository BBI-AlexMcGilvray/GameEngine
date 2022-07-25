#pragma once

#include <vector>

#include "Pipeline/ECS/DataOriented/ECS.h"
#include "Pipeline/UI/IMGUI/Window.h"

namespace Application {
namespace UI {
namespace IMGUI {
  class SystemTracker : public Window
  {
    public:
        SystemTracker()
        : Window("SystemTracker")
        {}

        void Draw() override;
    
    private:
        // ECS& _ecs;
  };
}// namespace IMGUI
}// namespace UI
}// namespace Application