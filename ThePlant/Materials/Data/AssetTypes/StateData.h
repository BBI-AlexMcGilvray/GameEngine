#pragma once

#include "Core/Math/Headers/Vector2.h"
#include "Core/Math/Headers/Vector3.h"

#include "Data/Headers/AssetMacros.h"

#include "Data/AssetTypes/EntityData.h"

namespace Data {
    NESTED_ASSET(PhysicsData,
        (Core::Math::Float3) gravity
    );

    ASSET(StateData,
        (PhysicsData) physics,
        (Core::Math::Float2) worldSize,
        (std::vector<AssetName<EntityData>>) entities,
        (std::vector<Core::Hash>) activeSystems
    );
    
ASSET_TYPE(StateData, "Resources/States/", ".st");
}// namespace Data