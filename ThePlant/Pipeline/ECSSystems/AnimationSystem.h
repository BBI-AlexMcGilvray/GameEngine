#pragma once

#include <vector>

#include "Pipeline/ECS/DataOriented/Systems/System.h"
#include "Pipeline/ECSSystems/AnimationComponents.h"

namespace Application {
struct AnimationSystem
{
    /*
        - Get all AnimatorComponents
            - Iterate and increase the 'animationTime' by a given delta time
            - Update the Animators accordingly
        - Get all AnimationComponents
            - For each, query the Animator for the given target
            - Apply the result to the affected components
    */
};
} // namespace Application