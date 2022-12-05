#pragma once

#include <vector>

#include "Core/Debugging/Profiling/Profiler.h"
#include "Core/Threading/Thread.h"

#include "Pipeline/UI/IMGUI/Window.h"

namespace Application {
namespace UI {
namespace IMGUI {
  /*
    We should keep X frames (make it a parameter) and provide a graph/the ability to scrub back/forward in time (like Unity/other profilers)
    We can also use IMGUI's graph functionality to display it nicely
  */
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

          DisplaySection(const Core::Profiling::Section& section)
          : tag(section.tag)
          , duration(Core::Second(0.0))
          , calls(0)
          {}

          void Update(const Core::Profiling::Section& section)
          {
            duration += section.end - section.start;
            calls += 1;
          }
        };

        bool update = true;
        std::unordered_map<Core::Threading::ThreadId, std::vector<DisplaySection>> threadSections;

        Profiler()
        : Window("Profiler")
        {}

        void OnDrawChange() override;
        void Draw() override;
  };
}// namespace IMGUI
}// namespace UI
}// namespace Application