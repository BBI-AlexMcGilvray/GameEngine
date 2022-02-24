#pragma once

#include "Core/Debugging/Profiling/Utils.h"

#include "Pipeline/ECS/DataOriented/EntitySnapshot.h"

namespace Application
{
namespace Collision
{
struct Collision
{
    EntitySnapshot entity1;
    EntitySnapshot entity2;
};

struct ICollisionHandler
{
    ICollisionHandler(const std::string& name, const TypeCollection& fromRequirements, const TypeCollection& toRequirements, bool applyToBoth)
    : _name(name)
    , _fromRequirements(fromRequirements)
    , _toRequirements(toRequirements)
    , _applyToBoth(applyToBoth)
    {}

    template <typename T>
    bool IsHandler() const { return (Core::GetTypeId<T>() == GetHandler()); }
    virtual Core::runtimeId_t GetHandler() const = 0;

    void Handle(Collision& collision) const
    {
        DEBUG_PROFILE_SCOPE(_name);

        // need to try both permutations
        if (collision.entity1.ContainsTypes(_fromRequirements) && collision.entity2.ContainsTypes(_toRequirements))
        {
            _Apply(collision.entity1, collision.entity2);
        }

        if (_applyToBoth)
        {
            if (collision.entity2.ContainsTypes(_fromRequirements) && collision.entity1.ContainsTypes(_toRequirements))
            {
                _Apply(collision.entity2, collision.entity1);
            }
        }
    }

protected:
    const std::string _name;
    const TypeCollection _fromRequirements;
    const TypeCollection _toRequirements;
    const bool _applyToBoth;

    // handlers only need to worry about apply the logic from 'from' to 'to'
    // if the other permutation should get applied, it is handled above
    virtual void _Apply(EntitySnapshot& from, EntitySnapshot& to) const = 0;
};

template <typename HANDLER>
struct CollisionHandler : public ICollisionHandler
{
    CollisionHandler(const std::string& name, const TypeCollection& fromRequirements, const TypeCollection& toRequirements, bool applyToBoth)
    : ICollisionHandler(name, fromRequirements, toRequirements, applyToBoth)
    {}
    
    Core::runtimeId_t GetHandler() const override
    {
        return Core::GetTypeId<HANDLER>();
    }
};

template <typename HANDLER>
struct StaticCollisionHandler : public CollisionHandler<HANDLER>
{
    StaticCollisionHandler(const std::string& name, const TypeCollection& fromRequirements, const TypeCollection& toRequirements, bool applyToBoth)
    : CollisionHandler<HANDLER>(name, fromRequirements, toRequirements, applyToBoth)
    {}

private:
    void _Apply(EntitySnapshot& from, EntitySnapshot& to) const override
    {
        HANDLER::ApplyCollision(from, to);
    }
};
} // namespace Collision
} // namespace Application