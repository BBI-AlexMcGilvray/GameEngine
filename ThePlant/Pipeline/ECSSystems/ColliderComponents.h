#pragma once

#include "Core/Geometric/GeometryDefs.h"

namespace Application
{
struct ColliderComponent
{
    Core::Geometric::Shape3D shape;
    bool trigger;
};

/*
Outline:
    - Collider has shape and if it is a trigger or not
    - Collider State system runs to generate an oct-tree first (for easier checks later)
        - See: https://www.kitware.com/octree-collision-imstk/
    - Collision system runs on oct tree to generate all Collisions
        - Collisions hold: EntitySnapshot for both entities in the collision
            - EntitySnapshot should have the EntityId it applies to, and a reference (tuple?) to each component it has at the time of the collision
                - If it is a reference (ideally, to avoid searching later), the ECS system can't change those entities for the time being
                - Should be fine since we use the DependencySystem to prevent that, and this is run soon after the Collider State system
    - Collision Handling system runs over all collisions to handle them
        - CollisionHandlers can be added
            - CollisionHandlers have a 'From' and a 'To' member that are a series of components (TypeCollection) that are required
            - For each collisions, each handler is checked (treating both entities in the collision as the 'from' or 'to' options) and applied if relevant
                - ex: DamageHandler requires 'From' to have 'DamageComponent' and 'To' to have 'HealthComponent'. If both entities have both components, both permutations are run through the handler
    - The oct-tree is kept for other systems to use
        - Ex: other system (input) wants to ray-cast to see if it hits anything

Notes:
    - We want a debug system to render the colliders
        - Ideally we can also use this to render points-of-collision when desired (or just turn the collided-colliders a different colour)
        - Also have a different colour for triggers (and if they have been triggered)
    - To make sure this is more clear and easily debuggable, we should put in a 'frame-step' debug option to allow us to step through 1 frame at a time if desired
        - The render loop can keep running if needed (using the last frame?)
        - If we can have the systems keep running but not apply further changes, that would be ideal for testing out/hitting breakpoints repeatedly
*/
} // namespace Application