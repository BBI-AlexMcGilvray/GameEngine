#pragma once

#include "Core/Headers/BitmaskEnum.h"

#include "Pipeline/Collision/Collisions.h"

namespace Application
{
namespace Collision
{
struct ICollisionHandler
{
    ICollisionHandler(const std::string& name, BitmaskEnum<CollisionState> handledStates, const TypeCollection& fromRequirements, const TypeCollection& toRequirements, bool applyToBoth)
    : _name(name)
    , _fromRequirements(fromRequirements)
    , _toRequirements(toRequirements)
    , _applyToBoth(applyToBoth)
    , _handledStates(handledStates)
    {}

    template <typename T>
    bool IsHandler() const { return (Core::GetTypeId<T>() == GetHandler()); }
    virtual Core::runtimeId_t GetHandler() const = 0;

    bool HandlesState(CollisionState state) const { return _handledStates.AtLeastOneFlag(state); }

    void Handle(StatefulCollision& collision) const
    {
        DEBUG_PROFILE_SCOPE(_name);

        if (!_handledStates.AtLeastOneFlag(collision.state))
        {
            return;
        }

        // need to try both permutations if the first doesn't work, otherwise we only do both if desired
        bool applied = false;
        if (collision.entity1.ContainsTypes(_fromRequirements) && collision.entity2.ContainsTypes(_toRequirements))
        {
            _Apply(collision.state, collision.collisionPoint, collision.entity1, collision.entity2);
            applied = true;
        }

        if (!applied || _applyToBoth)
        {
            if (collision.entity2.ContainsTypes(_fromRequirements) && collision.entity1.ContainsTypes(_toRequirements))
            {
                _Apply(collision.state, collision.collisionPoint, collision.entity2, collision.entity1);
            }
        }
    }

protected:
    const std::string _name;
    const TypeCollection _fromRequirements;
    const TypeCollection _toRequirements;
    const bool _applyToBoth;
    const BitmaskEnum<CollisionState> _handledStates;

    // handlers only need to worry about apply the logic from 'from' to 'to'
    // if the other permutation should get applied, it is handled above
    virtual void _Apply(const CollisionState collisionState, const Core::Geometric::Point3D& collisionPoint, EntitySnapshot& from, EntitySnapshot& to) const = 0;
};

template <typename HANDLER>
struct CollisionHandler : public ICollisionHandler
{
    CollisionHandler(const std::string& name, BitmaskEnum<CollisionState> handledStates, const TypeCollection& fromRequirements, const TypeCollection& toRequirements, bool applyToBoth)
    : ICollisionHandler(name, handledStates, fromRequirements, toRequirements, applyToBoth)
    {}
    
    Core::runtimeId_t GetHandler() const override
    {
        return Core::GetTypeId<HANDLER>();
    }
};

template <typename HANDLER>
struct StaticCollisionHandler : public CollisionHandler<HANDLER>
{
    StaticCollisionHandler(const std::string& name, BitmaskEnum<CollisionState> handledStates, const TypeCollection& fromRequirements, const TypeCollection& toRequirements, bool applyToBoth)
    : CollisionHandler<HANDLER>(name, handledStates, fromRequirements, toRequirements, applyToBoth)
    {}

private:
    void _Apply(const CollisionState collisionState, const Core::Geometric::Point3D& collisionPoint, EntitySnapshot& from, EntitySnapshot& to) const override
    {
        HANDLER::ApplyCollision(collisionState, collisionPoint, from, to);
    }
};
} // namespace Collision
} // namespace Application