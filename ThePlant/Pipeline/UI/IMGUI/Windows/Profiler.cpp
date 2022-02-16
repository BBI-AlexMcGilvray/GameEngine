#include "Pipeline/UI/IMGUI/Windows/Profiler.h"

#include <format>

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

void _DrawSection(Profiler::DisplaySection& section, const Core::Second& parentDuration)
{
    const Core::Second sectionDuration = section.end - section.start;

    ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x * (sectionDuration / parentDuration));
    ImGui::TableNextColumn();
    {
        ImGui::Checkbox("Show", &(section.unfolded));
        ImGui::Text("%s: %.5f ms", section.tag.c_str(), Core::Duration(sectionDuration) * 1000);
        if (section.unfolded)
        {
            if (ImGui::BeginTable(section.tag.c_str(), section.sections.size(), ImGuiTableFlags_Borders))
            {
                for (auto& nestedSection : section.sections)
                {
                    _DrawSection(nestedSection, sectionDuration);
                }
                ImGui::EndTable();
            }
        }
    }
    ImGui::PopItemWidth();
}

void Profiler::Draw()
{
    ImGui::Checkbox("Update profiler", &update);
    
    WITH_DEBUG_SERVICE(Profiling::Profiler)
    (
        _UpdateDisplaySections(*service, *this);
        
        if (!sections.empty())
        {
            ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(0.0f, 0.0f));
            if (ImGui::BeginTable("Profiler Data", sections.size(), ImGuiTableFlags_Borders))
            {
                auto totalDuration = Core::Second(0.0);
                for (auto& section : sections)
                {
                    ImGui::TableSetupColumn(section.tag.c_str());
                    totalDuration += section.end - section.start;
                }
                ImGui::TableHeadersRow();
                
                for (auto& section : sections)
                {
                    _DrawSection(section, totalDuration);
                }
                ImGui::EndTable();
            }
            ImGui::PopStyleVar(1);
        }
        else
        {
            ImGui::Text("No profile data");
        }
    )
}

}// namespace IMGUI
}// namespace UI
}// namespace Application