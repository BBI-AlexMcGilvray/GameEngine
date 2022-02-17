#pragma once

#include <vector>

#include "Pipeline/Debugging/Profiling/Profiler.h"
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
          Core::TimePoint start;
          Core::TimePoint end;
          std::vector<DisplaySection> sections;
          bool unfolded = false;
          bool ignore = false;

          DisplaySection(const Profiling::Section& section)
          : tag(section.tag)
          , start(section.start)
          , end(section.end)
          {
            for (const auto& nestedSection : section.sections)
            {
              sections.push_back(DisplaySection(nestedSection));
            }
          }

          void Update(const Profiling::Section& section)
          {
            tag = section.tag;
            start = section.start;
            end = section.end;
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