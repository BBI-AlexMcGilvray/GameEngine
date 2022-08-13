#pragma once

#include "Data/Headers/AssetMacros.h"
#include "Core/Serialization/Formats/JSON/JSON.h"

namespace Data {
// how do we do this? how do we have multiple different component types held in one vector without making each component it's own asset and stuff...
  NESTED_ASSET(ComponentData,
    (Core::Hash) componentType,
    (Core::Serialization::Format::JSON) componentData // json allows for easier modding/understanding. binary later if size/speed is an issue
  );

  ASSET(EntityData,
    (std::vector<ComponentData>) components
  );
}// namespace Rendering

ASSET_TYPE(EntityData, "Resources/Entities/", ".ent");
}// namespace Data