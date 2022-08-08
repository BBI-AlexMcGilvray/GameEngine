#pragma once

#include "Data/Headers/AssetMacros.h"

namespace Data {
// how do we do this? how do we have multiple different component types held in one vector without making each component it's own asset and stuff...
  NESTED_ASSET(ComponentData,
    (Core::Hash) componentType,
    (std::string) componentData // as json?
  );

  ASSET(EntityData,
    (std::vector<ComponentData>) components
  );
}// namespace Rendering

ASSET_TYPE(EntityData, "Resources/Entities/", ".ent");
}// namespace Data