#pragma once

#include "Pipeline/UI/IMGUI/Window.h"

namespace Application {
namespace UI {
namespace IMGUI {
  class Examples : public Window
  {
      public:
        Examples()
        : Window("Examples")
        {}

        void Draw() override;
  };
}// namespace IMGUI
}// namespace UI
}// namespace Application