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
            existingSection = displaySections.end() - 1;
            _UpdateDisplaySections(section.sections, existingSection->sections);
        }
    }

    // remove old sections
    for (auto& iter = displaySections.rbegin(); iter != displaySections.rend();)
    {
        auto newSection = std::find_if(sections.begin(), sections.end(), [tag = iter->tag](const auto& section)
        {
            return (tag == section.tag);
        });

        if (newSection == sections.end())
        {
            iter = std::make_reverse_iterator(displaySections.erase((iter + 1).base()));
        }
        else
        {
            ++iter;
        }
    }
}

void _ResetDisplaySectionDurations(std::vector<Profiler::DisplaySection>& displaySections)
{
    for (auto& section : displaySections)
    {
        section.duration = Core::Second(0.0);
        section.calls = 0;
        _ResetDisplaySectionDurations(section.sections);
    }
}

void _UpdateDisplaySections(const Profiling::Profiler& profiler, Profiler& window)
{
    if (!window.update)
    {
        return;
    }

    _ResetDisplaySectionDurations(window.sections);
    _UpdateDisplaySections(profiler.GetSections(), window.sections);
}

void _ResetDisplaySections(std::vector<Profiler::DisplaySection>& displaySections)
{
    for (auto& section : displaySections)
    {
        section.ignore = false;
        _ResetDisplaySections(section.sections);
    }
}

void _DrawSection(Profiler::DisplaySection& section, const Core::Second& parentDuration)
{
    float relativeDuration = section.duration / parentDuration;

    size_t activeSections = 0;
    for (auto& section : section.sections)
    {
        activeSections += section.ignore ? 0 : 1;
    }

    ImGui::TableNextColumn();
    {
        // section.ignore = ImGui::CollapsingHeader("Remove");
        // ImGui::SameLine();
        ImGui::ProgressBar(relativeDuration);

        section.unfolded = ImGui::CollapsingHeader("");
        ImGui::SameLine();
        ImGui::Text("[%i] %.3f ms -> %.3f ms/call", section.calls, Core::Duration(section.duration) * 1000, Core::Duration(section.duration) * 1000 / section.calls);
        if (section.unfolded && activeSections > 0)
        {
            if (ImGui::BeginTable(section.tag.c_str(), activeSections, ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable))
            {
                for (auto& nestedSection : section.sections)
                {
                    if (nestedSection.ignore)
                    {
                        continue;
                    }

                    ImGui::TableSetupColumn(nestedSection.tag.c_str());
                }
                ImGui::TableHeadersRow();

                for (auto& nestedSection : section.sections)
                {
                    if (nestedSection.ignore)
                    {
                        continue;
                    }

                    _DrawSection(nestedSection, section.duration);
                }
                ImGui::EndTable();
            }
        }
    }
}

void Profiler::Draw()
{
    ImGui::Checkbox("Update profiler", &update);
    // ImGui::SameLine();
    // if (ImGui::Button("Reset Profiler"))
    // {
    //     _ResetDisplaySections(sections);
    // }
    
    WITH_DEBUG_SERVICE(Profiling::Profiler)
    (
        _UpdateDisplaySections(*service, *this);
        
        if (!sections.empty())
        {
            size_t activeSections = 0;
            auto totalDuration = Core::Second(0.0);
            for (auto& section : sections)
            {
                activeSections += section.ignore ? 0 : 1;
                totalDuration += section.duration;
            }

            ImGui::Text("Framerate: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::Text("Total Frame Time: %.3f",  Core::Duration(totalDuration) * 1000);

            ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(0.0f, 0.0f));
            if (activeSections > 0 && ImGui::BeginTable("Profiler Data", activeSections, ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable))
            {
                for (auto& section : sections)
                {
                    if (section.ignore)
                    {
                        continue;
                    }

                    ImGui::TableSetupColumn(section.tag.c_str());
                }
                ImGui::TableHeadersRow();
                
                for (auto& section : sections)
                {
                    if (section.ignore)
                    {
                        continue;
                    }

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