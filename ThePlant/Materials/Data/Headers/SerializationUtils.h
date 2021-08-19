#pragma once

#include "Core/Serialization/Formats/JSON/JSON.h"

#include "Core/Headers/TimeDefs.h"

namespace Core::Serialization::Format
{
    void deserialize(Core::Second& time, std::shared_ptr<JSONNode> json);
    void deserialize(std::string& string, std::shared_ptr<JSONNode> json);
}