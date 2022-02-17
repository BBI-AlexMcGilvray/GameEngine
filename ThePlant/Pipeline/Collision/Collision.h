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
    ICollisionHandler(const std::string& name)
    : _name(name)
    {}

    virtual const TypeCollection& GetFromRequirements() const = 0;
    virtual const TypeCollection& GetToRequirements() const = 0;

    void Handle(Collision& collision) const
    {
        DEBUG_PROFILE_SCOPE(_name);

        const auto& fromRequirements = GetFromRequirements();
        const auto& toRequirements = GetToRequirements();

        // need to try both permutations
        if (collision.entity1.ContainsTypes(fromRequirements) && collision.entity2.ContainsTypes(toRequirements))
        {
            _Apply(collision.entity1, collision.entity2);
        }

        if (collision.entity2.ContainsTypes(fromRequirements) && collision.entity1.ContainsTypes(toRequirements))
        {
            _Apply(collision.entity2, collision.entity1);
        }
    }

private:
    const std::string _name;

    // handlers only need to worry about apply the logic from 'from' to 'to'
    // if the other permutation should get applied, it is handled above
    virtual void _Apply(EntitySnapshot& from, EntitySnapshot& to) const = 0;
};

template <typename HANDLER>
struct CollisionHandler : public ICollisionHandler
{
    CollisionHandler(const std::string& name)
    : ICollisionHandler(name)
    {}
    
private:
    void _Apply(EntitySnapshot& from, EntitySnapshot& to) const override
    {
        HANLDER::Handle(from, to);
    }
};
} // namespace Collision
} // namespace Application