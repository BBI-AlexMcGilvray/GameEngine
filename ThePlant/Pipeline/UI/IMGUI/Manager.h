#pragma once

#include "Pipeline/Headers/WindowManager.h"
#include "Pipeline/Headers/GLContextManager.h"

namespace Application {
namespace UI {
namespace IMGUI {
  class Manager
  {
    public:
    Manager(const WindowManager& window, const GLContextManager& glContext);

    // need to allow for adding/removing of active IMGUI windows
    // IMGUI windows should have IMGUI widgets/fields to make them more customizable?
    //      - maybe not, maybe that is not the point of how we use IMGUI

    void initialize();
    void start();

    void update();

    void end();
    void cleanUp();

    private:
      const WindowManager& _window;
      const GLContextManager& _glContext;
  };
}// namespace IMGUI
}// namespace UI
}// namespace Application