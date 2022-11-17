#include "Pipeline/Factory_Temp/UIUtils.h"

namespace Editor::UI
{
    /*
    NOTE: Imgui uses IDs to identify displays.
    See: https://github.com/ocornut/imgui/blob/master/docs/FAQ.md#q-how-can-i-have-widgets-with-an-empty-label

    summary: we probably need to pass in a label to act as an id here and distinguish between the displays
                - we may want to pass in a label and an option ID tag (could be the entity number?) to try and avoid issues
    */
    void ShowUI(bool& b, const std::string& text, const std::string& id)
    {
        std::string imguiString = IMGUITag(text, id);
        ImGui::Checkbox(imguiString.c_str(), &b);
    }

    void ShowUI(int& i, const std::string& text, const std::string& id)
    {
        std::string imguiString = IMGUITag(text, id);
        ImGui::DragInt(imguiString.c_str(), &i, DRAG_SPEED, DRAG_SPEED_MIN, DRAG_SPEED_MAX);
    }

    void ShowUI(Core::uint& u, const std::string& text, const std::string& id)
    {
        std::string imguiString = IMGUITag(text, id);
        ImGui::DragScalar(imguiString.c_str(), ImGuiDataType_U32, &u, DRAG_SPEED, &DRAG_SPEED_MIN, &DRAG_SPEED_MAX, "%l");
    }

    void ShowUI(float& f, const std::string& text, const std::string& id)
    {
        std::string imguiString = IMGUITag(text, id);
        ImGui::DragScalar(imguiString.c_str(), ImGuiDataType_Float, &f, DRAG_SPEED, &DRAG_SPEED_MIN, &DRAG_SPEED_MAX, "%f");
    }

    void ShowUI(double& d, const std::string& text, const std::string& id)
    {
        std::string imguiString = IMGUITag(text, id);
        ImGui::DragScalar(imguiString.c_str(), ImGuiDataType_Double, &d, DRAG_SPEED, &DRAG_SPEED_MIN, &DRAG_SPEED_MAX, "%d");
    }

    void ShowUI(std::string& str, const std::string& text, const std::string& id)
    {
        std::string imguiString = IMGUITag(text, id);
        ImGui::InputText(imguiString.c_str(), str.data(), str.max_size());
    }

    void ShowUI(const std::string& str, const std::string& text, const std::string& id)
    {
        std::string imguiString = IMGUITag(text, id);
        ImGui::LabelText(imguiString.c_str(), str.c_str());
    }

    void ShowUI(Core::Second& time, const std::string& text, const std::string& id)
    {
        float asFloat = Core::Duration(time);
        ShowUI(asFloat, text, id);        
    }

    void ShowUI(Core::Hash& hash, const std::string& text, const std::string& id)
    {
        // here, we probably want hashes to 'know' what type they are from (or string only?) and display that here instead
        Core::uint asUint = static_cast<Core::uint>(hash);
        ShowUI(asUint, text, id);
    }

    void ShowUI(Core::Math::Color& color, const std::string& text, const std::string& id)
    {
        std::string imguiString = IMGUITag(text, id);
        ImGui::ColorPicker4(imguiString.c_str(), &(color.RGBA[0]));
    }

    void ShowUI(Core::IO::FilePath& filePath, const std::string& text, const std::string& id)
    {
        std::string topString = IMGUITag(text, id);
        ImGui::Text(topString.c_str());
        
        ShowUI(filePath.File, "File", id);
        ShowUI(filePath.Path, "Path", id);
    }
} // namespace Editor::UI