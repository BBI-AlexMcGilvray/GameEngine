#pragma once

#include <vector>

#include "Core/Headers/Hash.h"
#include "Core/Serialization/Formats/JSON/JSON.h"

#include "Data/Headers/AssetMacros.h"

namespace Data {
// how do we do this? how do we have multiple different component types held in one vector without making each component it's own asset and stuff...
NESTED_ASSET(ComponentData,
  (std::string) componentType,
  (Core::Serialization::Format::JSON) componentData // json allows for easier modding/understanding. binary later if size/speed is an issue
);

ASSET(EntityData,
  (std::vector<ComponentData>) components
);

ASSET_TYPE(EntityData, "Resources/Entities/", ".ent");
}// namespace Data