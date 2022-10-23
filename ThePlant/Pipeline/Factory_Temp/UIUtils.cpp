#include "Pipeline/Factory_Temp/UIUtils.h"

namespace Core::Serialization::Format
{
    void CreateUI(int& i)
    {
        ImGui::DragInt("", &i, DRAG_SPEED, DRAG_SPEED_MIN, DRAG_SPEED_MAX);
    }

    void CreateUI(Core::uint& u)
    {
        ImGui::DragScalar("", ImGuiDataType_U32, &u, DRAG_SPEED, &DRAG_SPEED_MIN, &DRAG_SPEED_MAX, "%l");
    }

    void CreateUI(float& f)
    {
        ImGui::DragScalar("", ImGuiDataType_Float, &f, DRAG_SPEED, &DRAG_SPEED_MIN, &DRAG_SPEED_MAX, "%f");
    }

    void CreateUI(double& d)
    {
        ImGui::DragScalar("", ImGuiDataType_Double, &d, DRAG_SPEED, &DRAG_SPEED_MIN, &DRAG_SPEED_MAX, "%d");
    }

    void CreateUI(std::string& str)
    {
        ImGui::InputText(str.c_str(), str.data(), str.max_size());
    }

    void CreateUI(Core::Second& time)
    {
        float time = Core::Duration(time);
        CreateUI(time);        
    }

    void CreateUI(Core::Hash& hash)
    {
        // here, we probably want hashes to 'know' what type they are from (or string only?) and display that here instead
        CreateUI(static_cast<Core::uint&>(hash));
    }

    void CreateUI(Core::Math::Color& color)
    {
        ImGui::ColorPicker4("", &(color.RGBA[0]));
    }

    void CreateUI(Core::IO::FilePath& filePath)
    {
        ImGui::Text("File");
        ImGui::SameLine();
        CreateUI(filePath.File);

        ImGui::Text("Path");
        ImGui::SameLine();
        CreateUI(filePath.Path);
    }
}