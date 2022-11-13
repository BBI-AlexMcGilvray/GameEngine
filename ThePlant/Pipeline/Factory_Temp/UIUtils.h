#pragma once

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"
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
    static const float DRAG_SPEED_MIN = 0.00f;
    static const float DRAG_SPEED_MAX = 1.0f;

    void ShowUI(bool& b);
    void ShowUI(int& i);
    void ShowUI(Core::uint& u);
    void ShowUI(float& f);
    void ShowUI(double& d);
    void ShowUI(std::string& str);

    void ShowUI(Core::Second& time);
    void ShowUI(Core::Hash& hash);
    void ShowUI(Core::Math::Color& color);
    void ShowUI(Core::IO::FilePath& filePath);

    template <typename T>
    auto ShowUI(T& enumValue)
    -> typename std::enable_if<std::is_enum<T>::value>::type
    {
      // namespace may be an issue here. if it is, we may need the macro that creates this function to use the uppermost namespace (prefix with ::)
      ShowUI(to_string(enumValue)); // shouldn't be a string display, but a text display
    }

    // Ideally we find a way to make this generic for all enums that could be handled by it
    inline void ShowUI(::Data::Rendering::AnimationBehaviour& animationBehaviour)
    {
    //   ::Data::Rendering::from_string(data->GetData(), animationBehaviour);
    }
    // \Ideally we find a way to make this generic for all enums that could be handled by it

    template <typename T>
    inline void ShowUI(Data::AssetName<T>& asset)
    {
    //   asset = AsHash(static_cast<uint>(data->GetData()));
    }

    template <>
    inline void ShowUI<void>(Data::AssetName<void>& asset)
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
    void ShowUI(Core::Math::Vector2<T>& vector)
    {      
        ImGui::DragScalarN("", ImGuiDataType_Float, &(vector.XY[0]), 2, DRAG_SPEED, &DRAG_SPEED_MIN, &DRAG_SPEED_MAX);
    }

    template <typename T>
    void ShowUI(Core::Math::Vector3<T>& vector)
    {      
        ImGui::DragScalarN("", ImGuiDataType_Float, &(vector.XYZ[0]), 3, DRAG_SPEED, &DRAG_SPEED_MIN, &DRAG_SPEED_MAX);
    }

    template <typename T>
    void ShowUI(Core::Math::Vector4<T>& vector)
    {      
        ImGui::DragScalarN("", ImGuiDataType_Float, &(vector.XYZW[0]), 4, DRAG_SPEED, &DRAG_SPEED_MIN, &DRAG_SPEED_MAX);
    }

    template <typename T>
    void ShowUI(Core::Math::Quaternion<T>& quaternion)
    {
        ImGui::DragScalarN("", ImGuiDataType_Float, &(quaternion.XYZW[0]), 4, DRAG_SPEED, &DRAG_SPEED_MIN, &DRAG_SPEED_MAX);
    }

    // need matrix, and quaternion methods
    // also the serialization equivalents for all of the above
    // also the binary version(?)
    //      maybe only once everything is working, since json will be eaiser to debug until then
} // namespace Editor::UI