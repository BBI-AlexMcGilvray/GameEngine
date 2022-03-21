#pragma once

#include <vector>

#include "Core/Debugging/Memory/MemoryTracker.h"
#include "Pipeline/UI/IMGUI/Window.h"

namespace Application {
namespace UI {
namespace IMGUI {
  class MemoryTracker : public Window
  {
      std::string _currentMemoryInfo;

      public:
        MemoryTracker()
        : Window("MemoryTracker")
        {}

        void Draw() override;
  };
}// namespace IMGUI
}// namespace UI
}// namespace Application