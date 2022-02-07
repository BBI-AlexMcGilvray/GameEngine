#pragma once

#include <array>
#include <vector>

#include "Core/Headers/CoreDefs.h"
#include "Core/Geometric/Box.h"

#include "Pipeline/Collision/Collision.h"
#include "Pipeline/ECS/DataOriented/ECS.h"
#include "Pipeline/ECS/DataOriented/IDs.h"
#include "Pipeline/ECS/DataOriented/EntitySnapshot.h"
#include "Pipeline/ECSSystems/ColliderComponents.h"
#include "Pipeline/ECSSystems/TransformComponents.h"

namespace Application
{
namespace Collision
{
struct OctTreeContent
{
    const Core::Geometric::ShapeOrientation3D shapeOrientation;
    const EntityId entity; // content lasts a whole frame, can't hold snapshots

    OctTreeContent() = delete;
    OctTreeContent(const Core::Geometric::ShapeOrientation3D& shapeOrientation, const EntityId& entity)
    : shapeOrientation(shapeOrientation)
    , entity(entity)
    {}

    OctTreeContent(const OctTreeContent&) = default;
    OctTreeContent(OctTreeContent&&) = default;
    OctTreeContent& operator=(const OctTreeContent&) = default;
    OctTreeContent& operator=(OctTreeContent&&) = default;
};

class OctTreeNode;
OctTreeNode CreateOctTree(ECS& ecs, const Core::Math::Float3& totalSize);

/*
Notes:
    - We could optimize this class by having a non-one value for stop gapping content
        - ex: must have >8 items before they are no longer stop-gapped (as that now becomes more to check than there are children)
    - We could potentially also optimize by only nulling-out children that did not have content (to avoid consistently allocating new nodes)
*/
class OctTreeNode
{
    friend OctTreeNode CreateOctTree(ECS& ecs, const Core::Math::Float3& totalSize);

    public:
        OctTreeNode(OctTreeNode&&) = default;
        OctTreeNode& operator=(OctTreeNode&&) = default;

        OctTreeNode() = delete;
        OctTreeNode(const OctTreeNode&) = delete;
        OctTreeNode& operator=(const OctTreeNode&) = delete;

        // These just provide the entities that intersect with the provided shape
        EntitySnapshot FindFirstEntity(const Core::Geometric::ShapeOrientation3D& shape) const;
        std::vector<EntitySnapshot> FindAllEntities(const Core::Geometric::ShapeOrientation3D& shape) const;
    
        // to avoid having to repeatedly move stop-gapped content, the most efficient thing to do is to add content in order of descending size (biggest/least likely to be engulfed first)
        // so sort by Box[rotated > non-rotated]->Plane[infinite > finite]->Ray[infinite > finite]->Sphere[radius]->Point[-]
        void AddContent(const OctTreeContent& content); // adds item, to a child if possible (may require the creation of a new child if an appropriate one doesn't exist)
        // If the item would be in multiple children at once, it remains in the parent - only put into child if it fits entirely within in
        // maybe only creating children if multiple children are added (so we don't have one child creating an excessive amount of children)
        //      ex: adding a 'point' could would create children until the box was just that specific point in space - that is not needed

        // Collisions occur between two entities within the tree, nothing else
        std::vector<Collision> AllCollisions() const;

        void ClearTree();

    #if DEBUG
        const std::array<std::unique_ptr<OctTreeNode>, 8>& DEBUG_GetAllChildren() const;
        const Core::Geometric::ShapeOrientation<Core::Geometric::Box>& DEBUG_GetBounds() const;
        const std::vector<OctTreeContent>& DEBUG_GetAllContent() const;
    #endif

    private:
        static constexpr size_t NUMBER_OF_CHILDREN = 8;
        // EntitySnapshot is not the lightest thing to create, so create these first
        // Then we can create a map of EntityId->EntitySnapshot for all the entities that are in a collision
        // That way we can re-use the EntitySnapshots and avoid the duplicated effort
        struct IntermediaryCollision
        {
            const EntityId entity1;
            const EntityId entity2;

            IntermediaryCollision() = delete;
            IntermediaryCollision(const EntityId& entity1, const EntityId& entity2)
            : entity1(entity1)
            , entity2(entity2)
            {}

            IntermediaryCollision(IntermediaryCollision&&) = default;
            IntermediaryCollision& operator=(IntermediaryCollision&&) = default;

            IntermediaryCollision(const IntermediaryCollision&) = delete;
            IntermediaryCollision& operator=(const IntermediaryCollision&) = delete;
        };

        ECS& _ecs;
        const Core::Ptr<OctTreeNode> _parent;
        std::array<std::unique_ptr<OctTreeNode>, 8> _children;
        Core::Geometric::ShapeOrientation<Core::Geometric::Box> _this;
        // the above may not be the most efficient in making use of existing collision-detection logic, maybe want a specific 'AABB' box? maybe there is an intermediary workaround...
        std::vector<OctTreeContent> _content; // this way we can easily check for collisions and return the affected entity
        bool _stopGapped = false; // true only when the FIRST element has been placed into a fresh node (as a means to not drill-down forever)
        // the above would be generated by the colliders that are affected
        // std::vector<item-id-of-some-kind> _heldItemNames; // used to quickly search for a specific item? idk if needed, we shouldn't be using it in this way

    protected: // to allow inheritance so we can have hidden constructors
        OctTreeNode(ECS& ecs, const Core::Math::Float3& totalSize);
        OctTreeNode(ECS& ecs, const Core::Math::Float3& origin, const Core::Geometric::Box& box, const Core::Ptr<OctTreeNode> parent);

    private:
        void _CreateChildren();
        bool _ChildrenExist() const { return (_children[0] != nullptr); } // either all are made, or none are

        bool _Engulfs(const Core::Geometric::ShapeOrientation3D& data) const;
        OctTreeNode& _FindContainingNode(const Core::Geometric::ShapeOrientation3D& shape);
        const OctTreeNode& _FindContainingNode(const Core::Geometric::ShapeOrientation3D& shape) const;
        void _InsertContent(const OctTreeContent& content);
        void _StopGapContent(const OctTreeContent& content);
        void _RemoveStopGap();

        void _FindAllEntities(std::vector<EntitySnapshot>& entities, const Core::Geometric::ShapeOrientation3D& shape) const;
        void _InternalEntities(std::vector<EntitySnapshot>& entities, const Core::Geometric::ShapeOrientation3D& shape) const;
        void _EntitiesForAllContent(std::vector<EntitySnapshot>& entities) const;

        void _AllCollisions(std::vector<IntermediaryCollision>& collisions) const;
        void _InternalCollisions(std::vector<IntermediaryCollision>& collisions) const;
        void _CollisionsWithChildren(std::vector<IntermediaryCollision>& collisions) const;
        void _CollisionsWithAllContent(std::vector<IntermediaryCollision>& collisions, const OctTreeContent& content) const; // if we know the data collides with everything, quickly return all collisions
        void _FindAllCollisions(std::vector<IntermediaryCollision>& collisions, const OctTreeContent& content) const;
        void _ChildCollisions(std::vector<IntermediaryCollision>& collisions) const;

        std::vector<Collision> _CreateCollisions(const std::vector<IntermediaryCollision>& intermediaryCollisions) const;

    #ifdef DEBUG
        size_t _DEBUG_NumberOfContentIncludingChildren() const;
        const std::vector<Core::Geometric::ShapeOrientation3D> _DEBUG_AllChildShapes() const;
    #endif
};

using OctTree = OctTreeNode;

OctTreeNode CreateOctTree(ECS& ecs, const Core::Math::Float3& totalSize);
} // namespace Collision
} // namespace Application