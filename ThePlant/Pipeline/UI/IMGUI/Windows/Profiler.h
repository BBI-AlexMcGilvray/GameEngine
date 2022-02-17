#pragma once

#include <vector>

#include "Core/Debugging/Profiling/Profiler.h"
#include "Pipeline/UI/IMGUI/Window.h"

namespace Application {
namespace UI {
namespace IMGUI {
  class Profiler : public Window
  {
      public:
        struct DisplaySection
        {
          std::string tag;
          size_t calls;
          Core::Second duration;
          std::vector<DisplaySection> sections;
          bool unfolded = false;
          bool ignore = false;

          DisplaySection(const Profiling::Section& section)
          : tag(section.tag)
          , duration(section.end - section.start)
          , calls(1)
          {}

          void Update(const Profiling::Section& section)
          {
            tag = section.tag;
            duration += section.end - section.start;
            calls += 1;
          }
        };

        bool update = true;
        std::vector<DisplaySection> sections;

        Profiler()
        : Window("Profiler")
        {}

        void Draw() override;
  };
}// namespace IMGUI
}// namespace UI
}// namespace Application