#include "Pipeline/UI/IMGUI/Windows/Profiler.h"

#include "Core/Headers/Service.h"

namespace Application {
namespace UI {
namespace IMGUI {

void _UpdateDisplaySections(const std::vector<Profiling::Section>& sections, std::vector<Profiler::DisplaySection>& displaySections)
{
    // copy remaining sections over
    for (const auto& section : sections)
    {
        auto existingSection = std::find_if(displaySections.begin(), displaySections.end(), [tag = section.tag](const auto& displaySection)
        {
            return (tag == displaySection.tag);
        });

        if (existingSection != displaySections.end())
        {
            existingSection->Update(section);
            if (existingSection->unfolded)
            {
                _UpdateDisplaySections(section.sections, existingSection->sections);
            }
        }
        else
        {
            displaySections.push_back(section);
        }
    }

    // remove old sections
    for (auto& iter = displaySections.rbegin(); iter != displaySections.rend(); ++iter)
    {
        auto newSection = std::find_if(sections.begin(), sections.end(), [tag = iter->tag](const auto& section)
        {
            return (tag == section.tag);
        });

        if (newSection == sections.end())
        {
            displaySections.erase((iter + 1).base());
        }
    }
}

void _UpdateDisplaySections(const Profiling::Profiler& profiler, Profiler& window)
{
    if (!window.update)
    {
        return;
    }

    _UpdateDisplaySections(profiler.GetSections(), window.sections);
}

void _DrawSection(Profiler::DisplaySection& section)
{
    if (section.unfolded = ImGui::TreeNode(section.tag.c_str(), "%s: %d", section.tag.c_str(), (section.end - section.start).count()))
    {
        ImGui::Text("%d - %d", section.start, section.end);
        for (auto& nestedSection : section.sections)
        {
            _DrawSection(nestedSection);
        }
        ImGui::TreePop();
    }
}

void Profiler::Draw()
{
    ImGui::Checkbox("Update profiler", &update);
    
    WITH_DEBUG_SERVICE(Profiling::Profiler)
    (
        _UpdateDisplaySections(*service, *this);
        
        if (!sections.empty())
        {
            for (auto& section : sections)
            {
                _DrawSection(section);
            }
        }
        else
        {
            ImGui::Text("No sections profiled");
        }
    )
}

}// namespace IMGUI
}// namespace UI
}// namespace Application