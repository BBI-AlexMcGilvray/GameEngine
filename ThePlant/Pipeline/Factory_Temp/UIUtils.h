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

namespace Factory::UI
{
    static const float DRAG_SPEED = 0.005f;
    static const float DRAG_SPEED_MIN = 0.00f;
    static const float DRAG_SPEED_MAX = 1.0f;

    void CreateUI(int& i);
    void CreateUI(Core::uint& u);
    void CreateUI(float& f);
    void CreateUI(double& d);
    void CreateUI(std::string& str);

    void CreateUI(Core::Second& time);
    void CreateUI(Core::Hash& hash);
    void CreateUI(Core::Math::Color& color);
    void CreateUI(Core::IO::FilePath& filePath);

    // Ideally we find a way to make this generic for all enums that could be handled by it
    inline void CreateUI(::Data::Rendering::AnimationBehaviour& animationBehaviour)
    {
    //   ::Data::Rendering::from_string(data->GetData(), animationBehaviour);
    }
    // \Ideally we find a way to make this generic for all enums that could be handled by it

    template <typename T>
    inline void CreateUI(Data::AssetName<T>& asset)
    {
    //   asset = AsHash(static_cast<uint>(data->GetData()));
    }

    template <>
    inline void CreateUI<void>(Data::AssetName<void>& asset)
    {
    //   Hash name;
    //   Hash type;
    //   CreateUI(name, data->GetElement("name"));
    //   CreateUI(type, data->GetElement("type"));
    //   asset = Data::AssetName<void>(name, type);
    }

    // We should probably differentiate between JSONDecimal and JSONNumber based on the type of 'T'
    // that would make it less likely to lose data due to conversions, but we can leave as-is for now
    template <typename T>
    void CreateUI(Core::Math::Vector2<T>& vector)
    {      
        ImGui::DragScalarN("", ImGuiDataType_Float, &(vector.XY[0]), 2, DRAG_SPEED, &DRAG_SPEED_MIN, &DRAG_SPEED_MAX);
    }

    template <typename T>
    void CreateUI(Core::Math::Vector3<T>& vector)
    {      
        ImGui::DragScalarN("", ImGuiDataType_Float, &(vector.XYZ[0]), 3, DRAG_SPEED, &DRAG_SPEED_MIN, &DRAG_SPEED_MAX);
    }

    template <typename T>
    void CreateUI(Core::Math::Vector4<T>& vector)
    {      
        ImGui::DragScalarN("", ImGuiDataType_Float, &(vector.XYZW[0]), 4, DRAG_SPEED, &DRAG_SPEED_MIN, &DRAG_SPEED_MAX);
    }

    template <typename T>
    void CreateUI(Core::Math::Quaternion<T>& quaternion)
    {
        ImGui::DragScalarN("", ImGuiDataType_Float, &(quaternion.XYZW[0]), 4, DRAG_SPEED, &DRAG_SPEED_MIN, &DRAG_SPEED_MAX);
    }

    // need matrix, and quaternion methods
    // also the serialization equivalents for all of the above
    // also the binary version(?)
    //      maybe only once everything is working, since json will be eaiser to debug until then
}