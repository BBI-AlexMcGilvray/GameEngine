#pragma once

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"

#include "Core/Serialization/Formats/JSON/JSON.h"
#include "Core/Serialization/Serialization.h"

#include "Data/Headers/SerializationUtils.h"

#include "Pipeline/Rendering/Headers/Camera.h"

namespace Core::Serialization::Format
{
    void deserialize(Application::Rendering::Camera& camera, std::shared_ptr<JSONNode> json);
    std::shared_ptr<JSONNode> serialize(const Application::Rendering::Camera& camera);
}