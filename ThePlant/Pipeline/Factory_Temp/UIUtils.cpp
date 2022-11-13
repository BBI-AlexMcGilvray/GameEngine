#include "Pipeline/Factory_Temp/UIUtils.h"

namespace Editor::UI
{
    /*
    NOTE: Imgui uses IDs to identify displays.
    See: https://github.com/ocornut/imgui/blob/master/docs/FAQ.md#q-how-can-i-have-widgets-with-an-empty-label

    summary: we probably need to pass in a label to act as an id here and distinguish between the displays
                - we may want to pass in a label and an option ID tag (could be the entity number?) to try and avoid issues
    */
    void ShowUI(bool& b)
    {
        ImGui::Checkbox("", &b);
    }

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
        ImGui::InputText("", str.data(), str.max_size());
    }

    void ShowUI(const std::string& str)
    {
        ImGui::LabelText("", str.c_str());
    }

    void ShowUI(Core::Second& time)
    {
        float asFloat = Core::Duration(time);
        ShowUI(asFloat);        
    }

    void ShowUI(Core::Hash& hash)
    {
        // here, we probably want hashes to 'know' what type they are from (or string only?) and display that here instead
        Core::uint asUint = static_cast<Core::uint>(hash);
        ShowUI(asUint);
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