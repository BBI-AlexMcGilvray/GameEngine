#pragma once

#include <array>
#include <vector>

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/BitmaskEnum.h"
#include "Core/Geometric/AABB.h"
#include "Core/Geometric/AABBFunctions.h"

#include "Pipeline/Collision/Collisions.h"
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
    Core::Geometric::AABBShapeOrientation3D boundCollider;
    EntityId entity; // content lasts a whole frame, can't hold snapshots
    ColliderState state;

    OctTreeContent() = delete;
    OctTreeContent(const Core::Geometric::ShapeOrientation3D& shapeOrientation, const EntityId& entity, ColliderState state)
    : boundCollider(shapeOrientation)
    , entity(entity)
    , state(state)
    {}

    OctTreeContent(const OctTreeContent&) = default;
    OctTreeContent(OctTreeContent&&) = default;
    OctTreeContent& operator=(const OctTreeContent&) = default;
    OctTreeContent& operator=(OctTreeContent&&) = default;

    private:
    // these may need to be in the CollisionComponent, not here
    // friend struct OctTreeNode;
    // std::weak_ptr<OctTreeNode> _lastNode; // if this is not null, we start here and work our way up/down respectively
    // teleporting the collider may need to reset this, to not waste going up->down
    // this node should be provided to the 'AddContent' function as a 'hint' parameter
};

class OctTreeNode;
OctTreeNode CreateOctTree(ECS& ecs, const Core::Math::Float3& totalSize);

/*
Notes:
    - We could optimize this class by having a non-one value for stop gapping content
        - ex: must have >8 items before they are no longer stop-gapped (as that now becomes more to check than there are children)
    - We could potentially also optimize by only nulling-out children that did not have content (to avoid consistently allocating new nodes)
    - If we want to support a collision matrix (what collision tags interact with others) we can
        1. take in a matrix into the AllCollisions(...) function
        2. take in a matrix in the contstructor
        3. return all collisions and allow the CollisionManager to sort out/remove the collisions that don't 'actually' occur
        4. another system that takes in the collisions and sorts them somehow
        * in any case, we will probably want those tags to be on the collision component itself! (and maybe the OctTreeContent depending)
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
        std::pair<EntitySnapshot, Core::Geometric::Point3D> FindFirstEntity(const Core::Geometric::ShapeOrientation3D& shape) const;
        std::vector<std::pair<EntitySnapshot, Core::Geometric::Point3D>> FindAllEntities(const Core::Geometric::ShapeOrientation3D& shape) const;

        bool ContainsEntity(const EntityId& entity, bool checkChildren) const;
    
        // to avoid having to repeatedly move stop-gapped content, the most efficient thing to do is to add content in order of descending size (biggest/least likely to be engulfed first)
        // so sort by Box[rotated > non-rotated]->Plane[infinite > finite]->Ray[infinite > finite]->Sphere[radius]->Point[-]
        // ----
        // If the item would be in multiple children at once, it remains in the parent - only put into child if it fits entirely within in
        // maybe only creating children if multiple children are added (so we don't have one child creating an excessive amount of children)
        //      ex: adding a 'point' could would create children until the box was just that specific point in space - that is not needed
        void AddContent(const OctTreeContent& content);
        void AddStaticContent(const OctTreeContent& content);

        // Collisions occur between two entities within the tree, nothing else
        std::vector<Collision> AllCollisions() const;

        void ClearTree(bool clearStatics);

    #if DEBUG
        const std::array<std::unique_ptr<OctTreeNode>, 8>& DEBUG_GetAllChildren() const;
        const Core::Geometric::ShapeOrientation<Core::Geometric::AABB>& DEBUG_GetBounds() const;
        const std::vector<OctTreeContent>& DEBUG_GetAllContent() const;
    #endif

    private:
        static constexpr size_t NUMBER_OF_CHILDREN = 8;

        struct IntermediaryCollision
        {
            const EntityId entity1;
            const EntityId entity2;
            const Core::Math::Float3 collisionPoint;

            IntermediaryCollision() = delete;
            IntermediaryCollision(const EntityId& entity1, const EntityId& entity2, const Core::Math::Float3& collisionPoint)
            : entity1(entity1)
            , entity2(entity2)
            , collisionPoint(collisionPoint)
            {}

            IntermediaryCollision(IntermediaryCollision&&) = default;
            IntermediaryCollision& operator=(IntermediaryCollision&&) = default;

            IntermediaryCollision(const IntermediaryCollision&) = delete;
            IntermediaryCollision& operator=(const IntermediaryCollision&) = delete;
        };

        ECS& _ecs;
        const Core::Ptr<OctTreeNode> _parent;
        std::array<std::unique_ptr<OctTreeNode>, 8> _children;
        Core::Geometric::ShapeOrientation<Core::Geometric::AABB> _this;
        uint32_t _totalContentCount = 0; // # of entities held by this and child nodes
        std::vector<OctTreeContent> _content; // this way we can easily check for collisions and return the affected entity
        uint32_t _stopGapCount = 8; // only stop gapped once we have this much content
        // _moveContentOnStopGapRemoval being false -> faster tree building & slower collision finding
        // _moveContentOnStopGapRemoval being true -> slightly slower tree building & faster collision finding
        bool _moveContentOnStopGapRemoval = true; // if we should re-enter the content that was stop-gapped
        bool _stopGapped = false; // true only when the FIRST element has been placed into a fresh node (as a means to not drill-down forever)
        // the above would be generated by the colliders that are affected
        // std::vector<item-id-of-some-kind> _heldItemNames; // used to quickly search for a specific item? idk if needed, we shouldn't be using it in this way

    protected: // to allow inheritance so we can have hidden constructors
        OctTreeNode(ECS& ecs, const Core::Math::Float3& totalSize);
        OctTreeNode(ECS& ecs, const Core::Math::Float3& origin, const Core::Geometric::AABB& aabb, const Core::Ptr<OctTreeNode> parent);

    private:
        void _CreateChildren();
        inline bool _ChildrenExist() const { return (_children[0] != nullptr); } // either all are made, or none are
        inline bool _LeadsToContent() const { return _totalContentCount != 0; }

        bool _Engulfs(const Core::Geometric::AABBShapeOrientation3D& data) const;
        Core::Geometric::Intersection _Intersects(const Core::Geometric::AABBShapeOrientation3D& data) const;
        size_t _IndexForDirection(const Core::Math::Float3& direction) const;
        OctTreeNode& _FindContainingNode(const Core::Geometric::AABBShapeOrientation3D& shape);
        const OctTreeNode& _FindContainingNode(const Core::Geometric::AABBShapeOrientation3D& shape) const;
        void _InsertContent(const OctTreeContent& content);
        void _StopGapContent(const OctTreeContent& content);
        void _RemoveStopGap();

        enum class CheckDirection
        {
            Down = 1 << 0,
            Up = 1 << 1
        };
        std::pair<EntitySnapshot, Core::Geometric::Point3D> _FindFirstEntity(const Core::Geometric::AABBShapeOrientation3D& boundedShape, const BitmaskEnum<CheckDirection> checkDirection) const;

        void _FindAllEntities(std::vector<std::pair<EntitySnapshot, Core::Geometric::Point3D>>& entities, const Core::Geometric::AABBShapeOrientation3D& shape) const;
        void _InternalEntities(std::vector<std::pair<EntitySnapshot, Core::Geometric::Point3D>>& entities, const Core::Geometric::AABBShapeOrientation3D& shape) const;
        void _EntitiesForAllContent(std::vector<std::pair<EntitySnapshot, Core::Geometric::Point3D>>& entities) const;

        void _AllCollisions(std::vector<IntermediaryCollision>& collisions) const;
        void _InternalCollisions(std::vector<IntermediaryCollision>& collisions) const;
        void _CollisionsWithChildren(std::vector<IntermediaryCollision>& collisions) const;
        void _CollisionsWithAllContent(std::vector<IntermediaryCollision>& collisions, const OctTreeContent& content) const;
        void _FindAllCollisions(std::vector<IntermediaryCollision>& collisions, const OctTreeContent& content) const;
        void _ChildCollisions(std::vector<IntermediaryCollision>& collisions) const;

        std::vector<Collision> _CreateCollisions(const std::vector<IntermediaryCollision>& intermediaryCollisions) const;

        // returns how much content remains in node
        uint32_t _ClearNode(bool clearStatics);

    #ifdef DEBUG
        size_t _DEBUG_NumberOfContentIncludingChildren() const;
        const std::vector<Core::Geometric::ShapeOrientation3D> _DEBUG_AllChildShapes() const;
    #endif
};

using OctTree = OctTreeNode;

OctTreeNode CreateOctTree(ECS& ecs, const Core::Math::Float3& totalSize);
} // namespace Collision
} // namespace Application