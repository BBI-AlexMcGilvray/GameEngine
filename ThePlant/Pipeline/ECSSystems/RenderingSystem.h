#pragma once

#include <vector>

#include "Pipeline/ECS/DataOriented/Systems/System.h"
#include "Pipeline/ECSSystems/TransformComponents.h"
#include "Pipeline/ECSSystems/GeneralComponents.h"

namespace Application {
    // rendering system
    //  - one system for regular mesh rendering
    //  - one system for skinned mesh rendering
    //  - one system for skeleton bone updating
    //      - takes values from world transform and writes to the array of transforms for the bones
} // namespace Application