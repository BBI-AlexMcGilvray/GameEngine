#include "Pipeline/Factory_Temp/UIUtils.h"

namespace Editor::UI
{
    void ShowUI(int& i)
    {
        ImGui::DragInt("", &i, DRAG_SPEED, DRAG_SPEED_MIN, DRAG_SPEED_MAX);
    }

    void ShowUI(Core::uint& u)
    {
        ImGui::DragScalar("", ImGuiDataType_U32, &u, DRAG_SPEED, &DRAG_SPEED_MIN, &DRAG_SPEED_MAX, "%l");
    }

    void ShowUI(float& f)
    {
        ImGui::DragScalar("", ImGuiDataType_Float, &f, DRAG_SPEED, &DRAG_SPEED_MIN, &DRAG_SPEED_MAX, "%f");
    }

    void ShowUI(double& d)
    {
        ImGui::DragScalar("", ImGuiDataType_Double, &d, DRAG_SPEED, &DRAG_SPEED_MIN, &DRAG_SPEED_MAX, "%d");
    }

    void ShowUI(std::string& str)
    {
        ImGui::InputText(str.c_str(), str.data(), str.max_size());
    }

    void ShowUI(Core::Second& time)
    {
        float time = Core::Duration(time);
        ShowUI(time);        
    }

    void ShowUI(Core::Hash& hash)
    {
        // here, we probably want hashes to 'know' what type they are from (or string only?) and display that here instead
        ShowUI(static_cast<Core::uint&>(hash));
    }

    void ShowUI(Core::Math::Color& color)
    {
        ImGui::ColorPicker4("", &(color.RGBA[0]));
    }

    void ShowUI(Core::IO::FilePath& filePath)
    {
        ImGui::Text("File");
        ImGui::SameLine();
        ShowUI(filePath.File);

        ImGui::Text("Path");
        ImGui::SameLine();
        ShowUI(filePath.Path);
    }
} // namespace Editor::UI