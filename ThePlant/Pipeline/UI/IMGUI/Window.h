#pragma once

#include <string>

#include "Pipeline/Dependencies/IMGUI/imgui.h"

namespace Application {
namespace UI {
namespace IMGUI {
  class Window
  {
      public:
        bool draw = false;

        Window(const std::string& name, const bool& draw = false)
        : _name(name)
        , draw(draw)
        {}

        const std::string& GetName() const { return _name; }

        virtual void OnDrawChange() {}
        virtual void Draw() = 0;

      private:
        const std::string _name;
  };
}// namespace IMGUI
}// namespace UI
}// namespace Application