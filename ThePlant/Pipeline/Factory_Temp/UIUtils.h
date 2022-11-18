#pragma once

#include <limits>

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"
#include "Core/Headers/BitmaskEnum.h"
#include "Core/Headers/Hash.h"
#include "Core/Headers/TimeDefs.h"
#include "Core/Headers/CoreDefs.h"
#include "Core/Math/Headers/Color.h"
#include "Core/Math/Headers/Vector2.h"
#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/Vector4.h"
#include "Core/Math/Headers/Quaternion.h"
#include "Core/Serialization/Serialization.h"
#include "Core/IO/Headers/IODefs.h"

#include "Data/Headers/AssetName.h"
#include "Data/Rendering/Headers/SkeletonAnimationData.h" // is there a way to generisize this?

#include "Pipeline/Dependencies/IMGUI/imgui.h"

namespace Editor::UI
{
    static const float DRAG_SPEED = 0.005f;
    static const float DRAG_MIN = std::numeric_limits<float>::min();
    static const float DRAG_MAX = std::numeric_limits<float>::max();

    inline std::string IMGUITag(const std::string& text, const std::string& id)
    {
        return text + "##" + id;
    }

    void ShowUI(bool& b, const std::string& text, const std::string& id = "");
    void ShowUI(int& i, const std::string& text, const std::string& id = "");
    void ShowUI(Core::uint& u, const std::string& text, const std::string& id = "");
    void ShowUI(float& f, const std::string& text, const std::string& id = "");
    void ShowUI(double& d, const std::string& text, const std::string& id = "");
    void ShowUI(std::string& str, const std::string& text, const std::string& id = "");
    void ShowUI(const std::string& str, const std::string& text, const std::string& id = "");

    void ShowUI(Core::Second& time, const std::string& text, const std::string& id = "");
    void ShowUI(Core::Hash& hash, const std::string& text, const std::string& id = "");
    void ShowUI(Core::Math::Color& color, const std::string& text, const std::string& id = "");
    void ShowUI(Core::IO::FilePath& filePath, const std::string& text, const std::string& id = "");

    template <typename T>
    auto ShowUI(T& enumValue, const std::string& text, const std::string& id = "")
    -> typename std::enable_if<std::is_enum<T>::value>::type
    {
      // namespace may be an issue here. if it is, we may need the macro that creates this function to use the uppermost namespace (prefix with ::)
      const std::string enumString = to_string(enumValue);
      ShowUI(enumString, text, id); // shouldn't be a text display, but a selector - will need to use the meta_enum type stuff potentially to get the count and whatnot of given enums
    }

    template <typename T>
    void ShowUI(BitmaskEnum<T>& bitmaskValue, const std::string& text, const std::string& id = "")
    {
        // this should be a selectable where you turn on/off each option
        // the above should be a selectable drop down
    }

    template <typename T>
    inline void ShowUI(Data::AssetName<T>& asset, const std::string& text, const std::string& id = "")
    {
    //   asset = AsHash(static_cast<uint>(data->GetData()));
    }

    template <>
    inline void ShowUI<void>(Data::AssetName<void>& asset, const std::string& text, const std::string& id)
    {
    //   Hash name;
    //   Hash type;
    //   ShowUI(name, data->GetElement("name"));
    //   ShowUI(type, data->GetElement("type"));
    //   asset = Data::AssetName<void>(name, type);
    }

    // We should probably differentiate between JSONDecimal and JSONNumber based on the type of 'T'
    // that would make it less likely to lose data due to conversions, but we can leave as-is for now
    template <typename T>
    void ShowUI(Core::Math::Vector2<T>& vector, const std::string& text, const std::string& id = "")
    {      
        std::string imguiString = IMGUITag(text, id);
        ImGui::DragScalarN(imguiString.c_str(), ImGuiDataType_Float, &(vector.XY[0]), 2, DRAG_SPEED, &DRAG_MIN, &DRAG_MAX);
    }

    template <typename T>
    void ShowUI(Core::Math::Vector3<T>& vector, const std::string& text, const std::string& id = "")
    {      
        std::string imguiString = IMGUITag(text, id);
        ImGui::DragScalarN(imguiString.c_str(), ImGuiDataType_Float, &(vector.XYZ[0]), 3, DRAG_SPEED, &DRAG_MIN, &DRAG_MAX);
    }

    template <typename T>
    void ShowUI(Core::Math::Vector4<T>& vector, const std::string& text, const std::string& id = "")
    {      
        std::string imguiString = IMGUITag(text, id);
        ImGui::DragScalarN(imguiString.c_str(), ImGuiDataType_Float, &(vector.XYZW[0]), 4, DRAG_SPEED, &DRAG_MIN, &DRAG_MAX);
    }

    template <typename T>
    void ShowUI(Core::Math::Quaternion<T>& quaternion, const std::string& text, const std::string& id = "")
    {
        std::string imguiString = IMGUITag(text, id);
        ImGui::DragScalarN(imguiString.c_str(), ImGuiDataType_Float, &(quaternion.XYZW[0]), 4, DRAG_SPEED, &DRAG_MIN, &DRAG_MAX);
    }

    // need matrix, and quaternion methods
    // also the serialization equivalents for all of the above
    // also the binary version(?)
    //      maybe only once everything is working, since json will be eaiser to debug until then
} // namespace Editor::UI