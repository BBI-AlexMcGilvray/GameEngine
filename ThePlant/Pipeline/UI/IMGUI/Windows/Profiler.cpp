#include "Pipeline/UI/IMGUI/Windows/Profiler.h"

#include <format>

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"
#include "Core/Headers/Service.h"

namespace Application {
namespace UI {
namespace IMGUI {

void _ResetDisplaySectionDurations(std::vector<Profiler::DisplaySection>& displaySections)
{
    for (auto& section : displaySections)
    {
        section.duration = Core::Second(0.0);
        section.calls = 0;
        _ResetDisplaySectionDurations(section.sections);
    }
}

void _UpdateDisplaySections(const std::vector<Core::Profiling::Section>& sections, std::vector<Profiler::DisplaySection>& displaySections)
{
    SCOPED_MEMORY_CATEGORY("IMGUI");

    _ResetDisplaySectionDurations(displaySections);

    // copy remaining sections over
    for (const auto& section : sections)
    {
        auto existingSection = std::find_if(displaySections.begin(), displaySections.end(), [tag = section.tag](const auto& displaySection)
        {
            return (tag == displaySection.tag);
        });

        if (existingSection == displaySections.end())
        {
            displaySections.push_back(Profiler::DisplaySection(section));
            existingSection = displaySections.end() - 1;
        }
        
        existingSection->Update(section);
        _UpdateDisplaySections(section.sections, existingSection->sections);
    }

    // we need to only remove things if the section has been updated (ideally only at the top level for threads)
    // remove old sections
    for (auto iter = displaySections.begin(); iter != displaySections.end();)
    {
        auto newSection = std::find_if(sections.begin(), sections.end(), [tag = iter->tag](const auto& section)
        {
            return (tag == section.tag);
        });

        if (newSection == sections.end())
        {
            iter = displaySections.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
}

void _UpdateThreadDisplaySections(const std::unordered_map<Core::Threading::ThreadId, std::vector<Core::Profiling::Section>>& threadSections, std::unordered_map<Core::Threading::ThreadId, std::vector<Profiler::DisplaySection>>& displayThreadSections)
{
    SCOPED_MEMORY_CATEGORY("IMGUI");
    // copy remaining sections over
    for (auto& threadSection : threadSections)
    {
        const auto& sections = threadSection.second;
        auto& displaySections = displayThreadSections[threadSection.first];

        _UpdateDisplaySections(sections, displaySections);
    }
}

void _UpdateDisplaySections(Core::Profiling::Profiler& profiler, Profiler& window)
{
    if (!window.update)
    {
        return;
    }

    _UpdateThreadDisplaySections(profiler.GetThreadSectionsThenClear(), window.threadSections);
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
    SCOPED_MEMORY_CATEGORY("IMGUI");
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

void Profiler::OnDrawChange()
{
    WITH_DEBUG_SERVICE(Core::Profiling::Profiler)
    (
        service->collectData = draw;
    )
}

void Profiler::Draw()
{
    SCOPED_MEMORY_CATEGORY("IMGUI");
    ImGui::Checkbox("Update profiler", &update);
    // ImGui::SameLine();
    // if (ImGui::Button("Reset Profiler"))
    // {
    //     _ResetDisplaySections(sections);
    // }
    
    WITH_DEBUG_SERVICE(Core::Profiling::Profiler)
    (
        _UpdateDisplaySections(*service, *this);
        
        for (auto& threadSection : threadSections)
        {
            auto& sections = threadSection.second;
            if (!sections.empty())
            {
                size_t activeSections = 0;
                auto totalDuration = Core::Second(0.0);
                auto totalDurationPerFrame = Core::Second(0.0);
                for (auto& section : sections)
                {
                    activeSections += section.ignore ? 0 : 1;
                    totalDuration += section.duration;
                    if (section.sections.size() > 0)
                    {
                        totalDurationPerFrame += section.duration / section.calls;
                    }
                }

                ImGui::Text("Framerate: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                ImGui::Text("Total Time: %.3f",  Core::Duration(totalDuration) * 1000);
                ImGui::Text("Total Frame Time: %.3f",  Core::Duration(totalDurationPerFrame) * 1000);

                ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(0.0f, 0.0f));
                size_t threadIdHash = std::hash<Core::Threading::ThreadId>()(threadSection.first);
                std::string tableName = "Profiler Data - Thread " + std::to_string(threadIdHash);
                if (activeSections > 0 && ImGui::BeginTable(tableName.c_str(), activeSections, ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable))
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
        }
    )
}

}// namespace IMGUI
}// namespace UI
}// namespace Application