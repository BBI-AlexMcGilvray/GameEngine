#include "Pipeline/Collision/OctTree.h"

#include "Core/Geometric/Functions.h"

#include "Core/Debugging/Profiling/Utils.h"
#include "Core/Debugging/Memory/MemoryTrackerUtils.h"

namespace Application
{
namespace Collision
{
struct OctTree_Constructor : public OctTreeNode
{
    OctTree_Constructor(ECS& ecs, const Core::Math::Float3& origin, const Core::Geometric::AABB& aabb, const Core::Ptr<OctTreeNode> parent)
    : OctTreeNode(ecs, origin, aabb, parent)
    {}
};

OctTreeNode::OctTreeNode(ECS& ecs, const Core::Math::Float3& totalSize)
: OctTree(ecs, Core::Math::Float3(0.0f), Core::Geometric::AABB(totalSize), nullptr)
{}

OctTreeNode::OctTreeNode(ECS& ecs, const Core::Math::Float3& origin, const Core::Geometric::AABB& aabb, const Core::Ptr<OctTreeNode> parent)
: _ecs(ecs)
, _parent(parent)
, _this{ Core::Geometric::Orientation(origin), aabb }
{}

std::pair<EntitySnapshot, Core::Geometric::Point3D> OctTreeNode::FindFirstEntity(const Core::Geometric::ShapeOrientation3D& shape) const
{
    Core::Geometric::AABBShapeOrientation3D boundedShape(shape);
    const OctTreeNode& containingNode = _FindContainingNode(shape);
    for (const auto& content : containingNode._content)
    {
        if (const auto intersection = Core::Geometric::Intersect(content.boundCollider, boundedShape); intersection.intersect)
        {
            return { _ecs.GetTemporaryEntitySnapshot(content.entity), intersection.point };
        }
    }

    // maybe we collide with a parent's content if we have a parent
    if (_parent == nullptr)
    {
        return { EntitySnapshot(), Core::Geometric::Point3D() };
    }
    return _parent->FindFirstEntity(shape);
}

std::vector<std::pair<EntitySnapshot, Core::Geometric::Point3D>> OctTreeNode::FindAllEntities(const Core::Geometric::ShapeOrientation3D& shape) const
{
    DEBUG_PROFILE_SCOPE("OctTreeNode::FindAllEntities");

    std::vector<std::pair<EntitySnapshot, Core::Geometric::Point3D>> entities;
    // not calling '_FindContainingNode' because we want EVERYTHING it may intersect with, so we may as well start from the top
    _FindAllEntities(entities, Core::Geometric::AABBShapeOrientation3D(shape));
    return entities;
}

bool OctTreeNode::ContainsEntity(const EntityId& entity, bool checkChildren) const
{
    DEBUG_PROFILE_SCOPE("OctTreeNode::ContainsEntity");
    for (const auto& content : _content)
    {
        if (content.entity == entity)
        {
            return true;
        }
    }

    if (checkChildren && _ChildrenExist())
    {
        for (const auto& child : _children)
        {
            if (child->_LeadsToContent() && child->ContainsEntity(entity, checkChildren))
            {
                return true;
            }
        }
    }

    return false;
}

void OctTreeNode::AddContent(const OctTreeContent& content)
{
    DEBUG_PROFILE_SCOPE("OctTreeNode::AddContent");
#if DEBUG
    // VERIFY(_parent != nullptr || _Engulfs(content.shapeOrientation));// All content should exist WITHIN the topmost node
#endif

    // debug logic to check if content already exists?
    _InsertContent(content);
}

void OctTreeNode::AddStaticContent(const OctTreeContent& content)
{
    DEBUG_PROFILE_SCOPE("OctTreeNode::AddStaticContent");
    AddContent(content);
}

// why is this still so slow... is it because the tree isn't being used at the moment? -> definitely sped up SIGNIFICANTLY by the tree!
std::vector<Collision> OctTreeNode::AllCollisions() const
{
    DEBUG_PROFILE_SCOPE("OctTreeNode::AllCollisions");

    std::vector<IntermediaryCollision> intermediaryCollisions;
    _AllCollisions(intermediaryCollisions);
    return _CreateCollisions(intermediaryCollisions);
}

void OctTreeNode::ClearTree(bool clearStatics)
{
    DEBUG_PROFILE_SCOPE("OctTreeNode::ClearTree");

    _ClearNode(clearStatics);
}

#if DEBUG
const std::array<std::unique_ptr<OctTreeNode>, 8>& OctTreeNode::DEBUG_GetAllChildren() const
{
    return _children;
}

const Core::Geometric::ShapeOrientation<Core::Geometric::AABB>& OctTreeNode::DEBUG_GetBounds() const
{
    return _this;
}

const std::vector<OctTreeContent>& OctTreeNode::DEBUG_GetAllContent() const
{
    return _content;
}
#endif

void OctTreeNode::_CreateChildren()
{
    SCOPED_MEMORY_CATEGORY("Collision");

    if ( _ChildrenExist())
    {
        return;
    }

    const Core::Geometric::AABB childBounds(_this.shape.dimensions * 0.5f);
    const Core::Math::Float3 childOriginOffset = childBounds.dimensions * 0.5f;

    // double check this math?
    for (size_t i = 0; i < NUMBER_OF_CHILDREN; ++i)
    {
        Core::Math::Float3 childDirection(0.0f);
        childDirection.X += childOriginOffset.X * (i < 4 ? 1 : -1); // [0, 3] are x > 0
        childDirection.Y += childOriginOffset.Y * (i < 2 || (i > 3 && i < 6) ? 1 : -1); // [0, 1] and [4, 5] are y > 0
        childDirection.Z += childOriginOffset.Z * (i % 2 ? 1 : -1); // even numbers are z > 0

        Core::Math::Float3 childOrigin = _this.orientation.position + childDirection;

        _children[_IndexForDirection(childDirection)] = std::make_unique<OctTree_Constructor>(_ecs, childOrigin, childBounds, this);
    }
}

bool OctTreeNode::_Engulfs(const Core::Geometric::AABBShapeOrientation3D& shape) const
{
    // we may want to take these 'double check' intersect calls and move them to a generic method
    // particularly to NOT use bounding boxes when the shapes don't warrant them (points, spheres)
    return Core::Geometric::Engulfs(_this, shape.boundingBox); // && Core::Geometric::Engulfs(Core::Geometric::RemoveAA(_this), shape.shapeOrientation); // don't need the second for this purpose
}

Core::Geometric::Intersection OctTreeNode::_Intersects(const Core::Geometric::AABBShapeOrientation3D& shape) const
{
    // we may want to take these 'double check' intersect calls and move them to a generic method
    // particularly to NOT use bounding boxes when the shapes don't warrant them (points, spheres)
    return Core::Geometric::Intersect(_this, shape.boundingBox);// && Core::Geometric::Intersect(Core::Geometric::RemoveAA(_this), shape.shapeOrientation); // don't need the second for this purpose
}

size_t OctTreeNode::_IndexForDirection(const Core::Math::Float3& direction) const
{
    // at this level, we know the shape is engulfed by _this_ node, so just check the one that could possibly hold the shape (the one the shape's center is is)

    size_t index = direction.X > 0.0f ? 0 : 4; // [0, 3] are x > 0
    index += direction.Y > 0.0f ? 0 : 2; // [0, 1] and [4, 5] are y > 0
    index += direction.Z > 0.0f ? 0 : 1; // even numbers are z > 0

    return index;
}

// must be tied with the above
OctTreeNode& OctTreeNode::_FindContainingNode(const Core::Geometric::AABBShapeOrientation3D& shape)
{
    // DEBUG_PROFILE_SCOPE("OctTreeNode::_FindContainingNode");

    if (!_ChildrenExist())
    {
        return *this;
    }

    const auto direction = shape.shapeOrientation.orientation.position - _this.orientation.position;
    const auto& likelyContainingChild = _children[_IndexForDirection(direction)];
    // if we keep track of the last node holding an object was in we could go through that list? it shouldn't be this expensive... -> maybe because it is a debug build?
    if (likelyContainingChild->_Engulfs(shape))
    {   // this can go quite deep, likely contributing to the overall cost... how can we make it stop early?
        return likelyContainingChild->_FindContainingNode(shape);
    }

    return *this;
}

// must be tied with the above
const OctTreeNode& OctTreeNode::_FindContainingNode(const Core::Geometric::AABBShapeOrientation3D& shape) const
{
    if (!_ChildrenExist())
    {
        return *this;
    }

    const auto direction = shape.shapeOrientation.orientation.position - _this.orientation.position;
    const auto& likelyContainingChild = _children[_IndexForDirection(direction)];
    if (likelyContainingChild->_Engulfs(shape))
    {
        return likelyContainingChild->_FindContainingNode(shape);
    }

    return *this;
}

void OctTreeNode::_InsertContent(const OctTreeContent& content)
{
    SCOPED_MEMORY_CATEGORY("Collision");
    // DEBUG_PROFILE_SCOPE("OctTreeNode::_InsertContent");

    ++_totalContentCount;

    if (_content.empty() && !_ChildrenExist())
    {
        _StopGapContent(content);
        return;
    }

    DEBUG_PROFILE_PUSH("_CreateChildren");
    _CreateChildren();
    DEBUG_PROFILE_POP("_CreateChildren");

    if (_stopGapped)
    {
        _RemoveStopGap();
    }
    
    // insert the new content
    DEBUG_PROFILE_PUSH("_FindContainingNode");
    auto& newContentContainer = _FindContainingNode(content.boundCollider);
    DEBUG_PROFILE_POP("_FindContainingNode");
    if (&newContentContainer == this)
    {
        _content.push_back(content);
        return;
    }
    newContentContainer._InsertContent(content);
}

void OctTreeNode::_StopGapContent(const OctTreeContent& content)
{
    SCOPED_MEMORY_CATEGORY("Collision");
    _content.push_back(content);
    _stopGapped = true;
}

void OctTreeNode::_RemoveStopGap()
{
    // DEBUG_PROFILE_SCOPE("OctTreeNode::_RemoveStopGap");

    _stopGapped = false;
    OctTreeContent stopGappedContent = _content.back();
    _content.pop_back();
    auto& stopGappedContainer = _FindContainingNode(stopGappedContent.boundCollider);
    stopGappedContainer._InsertContent(stopGappedContent); // now that the tree has been expanded, try to move the stop-gapped content down a layer
}

void OctTreeNode::_FindAllEntities(std::vector<std::pair<EntitySnapshot, Core::Geometric::Point3D>>& entities, const Core::Geometric::AABBShapeOrientation3D& shape) const
{
    // DEBUG_PROFILE_SCOPE("OctTreeNode::_FindAllEntities");

    _InternalEntities(entities, shape);

    if (!_ChildrenExist())
    {
        return;
    }

    // review this and similar logic - does it make sense?
    for (const auto& child : _children)
    {
        if (!child->_LeadsToContent())
        {
            continue;
        }

        if (Core::Geometric::Engulfs(shape.boundingBox, child->_this))
        {
            if (Core::Geometric::Engulfs(shape.shapeOrientation, Core::Geometric::RemoveAA(child->_this)))
            {
                child->_EntitiesForAllContent(entities);
            }
            else
            {
                child->_FindAllEntities(entities, shape);
            }
        }
        else if (const auto intersection = Core::Geometric::Intersect(shape.boundingBox, child->_this); intersection.intersect)
        {
            child->_FindAllEntities(entities, shape);
        }
    }
}

void OctTreeNode::_InternalEntities(std::vector<std::pair<EntitySnapshot, Core::Geometric::Point3D>>& entities, const Core::Geometric::AABBShapeOrientation3D& shape) const
{
    SCOPED_MEMORY_CATEGORY("Collision");
    // DEBUG_PROFILE_SCOPE("OctTreeNode::_InternalEntities");

    for (const auto& content : _content)
    {
        // we may want to take these 'double check' intersect calls and move them to a generic method
        // particularly to NOT use bounding boxes when the shapes don't warrant them (points, spheres)
        if (const auto intersection = Core::Geometric::Intersect(content.boundCollider, shape); intersection.intersect)
        {
            entities.push_back({ _ecs.GetTemporaryEntitySnapshot(content.entity), intersection.point });
        }
    }
}

void OctTreeNode::_EntitiesForAllContent(std::vector<std::pair<EntitySnapshot, Core::Geometric::Point3D>>& entities) const
{
    SCOPED_MEMORY_CATEGORY("Collision");
    // DEBUG_PROFILE_SCOPE("OctTreeNode::_EntitiesForAllContent");

    for (const auto& content : _content)
    {
        entities.push_back({ _ecs.GetTemporaryEntitySnapshot(content.entity), content.boundCollider.shapeOrientation.orientation.position });
    }

    if (!_ChildrenExist())
    {
        return;
    }

    for (const auto& child : _children)
    {
        if (!child->_LeadsToContent())
        {
            continue;
        }

        child->_EntitiesForAllContent(entities);
    }
}

void OctTreeNode::_AllCollisions(std::vector<IntermediaryCollision>& collisions) const
{
    // DEBUG_PROFILE_SCOPE("OctTreeNode::_AllCollisions");

    _InternalCollisions(collisions);
    _CollisionsWithChildren(collisions);
    _ChildCollisions(collisions);
}

void OctTreeNode::_InternalCollisions(std::vector<IntermediaryCollision>& collisions) const
{
    SCOPED_MEMORY_CATEGORY("Collision");
    // DEBUG_PROFILE_SCOPE("OctTreeNode::_InternalCollisions");

    // edge case covering due to _content.size() - 1 in loop
    if (_content.size() == 0)
    {
        return;
    }

    for (size_t i = 0; i < _content.size() - 1; ++i)
    {
        // we need to iterate over statics too, since they are kept and will be the first elements in the vector, so wouldn't be checked otherwise
        bool firstIsStatic = (_content[i].state == ColliderState::Static_Placed);

        for (size_t j = i + 1; j < _content.size(); ++j)
        {
            if (firstIsStatic && _content[j].state == ColliderState::Static_Placed)
            {
                // 2 static colliders do not count as 'colliding' as it would never end
                continue;
            }

            // we may want to take these 'double check' intersect calls and move them to a generic method
            // particularly to NOT use bounding boxes when the shapes don't warrant them (points, spheres)
            if (Core::Geometric::Intersection intersection = Core::Geometric::Intersect(_content[i].boundCollider, _content[j].boundCollider); intersection.intersect)
            {
                collisions.push_back(IntermediaryCollision(_content[i].entity, _content[j].entity, intersection.point));
            }
        }
    }
}

void OctTreeNode::_CollisionsWithChildren(std::vector<IntermediaryCollision>& collisions) const
{
    // DEBUG_PROFILE_SCOPE("OctTreeNode::_CollisionsWithChildren");

    if (!_ChildrenExist())
    {
        return;
    }

    // instead of going down the whole tree for each object, it is probably better to go down the tree and gather a collection of 'possible objects' to check intersections with
    // this way we traverse the tree once instead of going up and down several times
    // worth trying anyways, but i wonder why that would be faster - maybe just jumping around in memory less?
    for (size_t i = 0; i < _content.size(); ++i)
    {
        for (const auto& child : _children)
        {
            if (!child->_LeadsToContent())
            {
                continue;
            }
            
            if (Core::Geometric::Engulfs(_content[i].boundCollider.boundingBox, child->_this))
            {
                if (Core::Geometric::Engulfs(_content[i].boundCollider.shapeOrientation, Core::Geometric::RemoveAA(child->_this)))
                {
                    child->_CollisionsWithAllContent(collisions, _content[i]);
                }
                else
                {
                    child->_FindAllCollisions(collisions, _content[i]);
                }
                continue;
            }

            if (const auto intersection = Core::Geometric::Intersect(_content[i].boundCollider.boundingBox, child->_this); intersection.intersect)
            {
                child->_FindAllCollisions(collisions, _content[i]);
            }
        }
    }
}

void OctTreeNode::_CollisionsWithAllContent(std::vector<IntermediaryCollision>& collisions, const OctTreeContent& content) const
{
    SCOPED_MEMORY_CATEGORY("Collision");
    // DEBUG_PROFILE_SCOPE("OctTreeNode::_CollisionsWithAllContent");

    for (const auto& c : _content)
    {
        // when engulfed, use the position of the object being engulfed
        collisions.push_back(IntermediaryCollision(c.entity, content.entity, c.boundCollider.shapeOrientation.orientation.position));
    }

    if (!_ChildrenExist())
    {
        return;
    }

    for (const auto& child : _children)
    {
        if (!child->_LeadsToContent())
        {
            continue;
        }

        child->_CollisionsWithAllContent(collisions, content);
    }
}

void OctTreeNode::_FindAllCollisions(std::vector<IntermediaryCollision>& collisions, const OctTreeContent& content) const
{
    SCOPED_MEMORY_CATEGORY("Collision");
    // DEBUG_PROFILE_SCOPE("OctTreeNode::_FindAllCollisions");

    for (const auto& c : _content)
    {
        // we may want to take these 'double check' intersect calls and move them to a generic method
        // particularly to NOT use bounding boxes when the shapes don't warrant them (points, spheres)
        if (Core::Geometric::Intersection intersection = Core::Geometric::Intersect(c.boundCollider, content.boundCollider); intersection.intersect)
        {
            collisions.push_back(IntermediaryCollision(c.entity, content.entity, intersection.point));
        }
    }

    if (!_ChildrenExist())
    {
        return;
    }

    for (const auto& child : _children)
    {
        if (!child->_LeadsToContent())
        {
            continue;
        }

        if (Core::Geometric::Engulfs(content.boundCollider.boundingBox, child->_this))
        {
            if (Core::Geometric::Engulfs(content.boundCollider.shapeOrientation, Core::Geometric::RemoveAA(child->_this)))
            {
                child->_CollisionsWithAllContent(collisions, content);
            }
            else
            {
                child->_FindAllCollisions(collisions, content);
            }
        }
        else if (const auto intersection = Core::Geometric::Intersect(content.boundCollider.boundingBox, child->_this); intersection.intersect)
        {
            child->_FindAllCollisions(collisions, content);
        }
    #ifdef DEBUG // may want to remove this debug one confident in functionality/comment it out to avoid performance hits
        // else
        // {
        //     // for debugging, get all children and explicitly check them. if any children are collided with but not checked throw an error
        //     const auto allChildShapes = child->_DEBUG_AllChildShapes();
        //     for (const auto& childShape : allChildShapes)
        //     {
        //         if (const auto intersection = Core::Geometric::Intersect(content.boundCollider.shapeOrientation, childShape); intersection.intersect)
        //         {
        //             CORE_THROW("OctTree", "An collision was missed due to OctTree not checking for collisions properly");
        //         }
        //     }
        // }
    #endif
    }
}

void OctTreeNode::_ChildCollisions(std::vector<IntermediaryCollision>& collisions) const
{
    // DEBUG_PROFILE_SCOPE("OctTreeNode::_ChildCollisions");

    if (!_ChildrenExist())
    {
        return;
    }

    for (const auto& child : _children)
    {
        if (!child->_LeadsToContent())
        {
            continue;
        }
        
        child->_AllCollisions(collisions);
    }
}

std::vector<Collision> OctTreeNode::_CreateCollisions(const std::vector<IntermediaryCollision>& intermediaryCollisions) const
{
    SCOPED_MEMORY_CATEGORY("Collision");
    // DEBUG_PROFILE_SCOPE("OctTreeNode::_CreateCollisions");
    
    // NOTE: The below needs to be tested!
    // EntitySnapshot is not the lightest thing to create, so create these first
    // Then we can create a map of EntityId->EntitySnapshot for all the entities that are in a collision
    // That way we can re-use the EntitySnapshots and avoid the duplicated effort
    std::unordered_map<EntityId, EntitySnapshot> snapshots;
    for (const auto& intermediaryCollision : intermediaryCollisions)
    {
        if (snapshots.find(intermediaryCollision.entity1) == snapshots.end())
        {
            snapshots[intermediaryCollision.entity1] = _ecs.GetTemporaryEntitySnapshot(intermediaryCollision.entity1);
        }
        if (snapshots.find(intermediaryCollision.entity2) == snapshots.end())
        {
            snapshots[intermediaryCollision.entity2] = _ecs.GetTemporaryEntitySnapshot(intermediaryCollision.entity2);
        }
    }

    std::vector<Collision> collisions;
    collisions.reserve(intermediaryCollisions.size());
    for (const auto& intermediaryCollision : intermediaryCollisions)
    {
        collisions.emplace_back<Collision>({ snapshots[intermediaryCollision.entity1], snapshots[intermediaryCollision.entity2], intermediaryCollision.collisionPoint });
    }
    
    return collisions;
}

uint32_t OctTreeNode::_ClearNode(bool clearStatics)
{
    _totalContentCount = 0;
    bool canDelete = true;

    if (_ChildrenExist())
    {
        for (auto& child : _children)
        {
            _totalContentCount += child->_ClearNode(clearStatics);
            canDelete &= (_totalContentCount == 0);
        }
        if (canDelete)
        {
            _children = { nullptr };
        }
    }

    bool hasContent = _content.size() > 0;
    if (hasContent)
    {
        for (size_t index = _content.size(); index > 0; --index)
        {
            size_t trueIndex = index - 1;
            const auto& content = _content[trueIndex];
            bool isStatic = content.state == ColliderState::Static_Placed;
            if (!isStatic || clearStatics)
            {
                _content.erase(_content.begin() + trueIndex);
            }
            else
            {
                ++_totalContentCount;
            }
        }
    }
    
    // the below also helps us avoid inserting the same object several times due to false stop-gaps!
    canDelete &= !hasContent && _content.empty(); // only delete the node if it goes 2 frames without content (to avoid reallocating for the same stuff)
    if (canDelete)
    {   // this is what saves us from stop-gapping repeatedly
        _stopGapped = false;
    }

    return _totalContentCount;
}

#ifdef DEBUG
size_t OctTreeNode::_DEBUG_NumberOfContentIncludingChildren() const
{
    size_t totalCount = _content.size();
    
    if (_ChildrenExist())
    {
        for (const auto& child : _children)
        {
            totalCount += child->_DEBUG_NumberOfContentIncludingChildren();
        }
    }

    VERIFY(totalCount == _totalContentCount, "If these aren't equal then we have a big problem, this is what _totalContentCount is supposed to do!");
    return totalCount;
}

const std::vector<Core::Geometric::ShapeOrientation3D> OctTreeNode::_DEBUG_AllChildShapes() const
{
    SCOPED_MEMORY_CATEGORY("Collision");
    std::vector<Core::Geometric::ShapeOrientation3D> allChildShapes;

    if (_ChildrenExist())
    {
        for (const auto& child : _children)
        {
            for (const auto& content : child->_content)
            {
                allChildShapes.push_back(content.boundCollider.shapeOrientation);
            }

            auto childShapes = child->_DEBUG_AllChildShapes();
            allChildShapes.insert(allChildShapes.end(), childShapes.begin(), childShapes.end());
        }
    }

    return allChildShapes;
}
#endif

OctTreeNode CreateOctTree(ECS& ecs, const Core::Math::Float3& totalSize)
{
#ifdef DEBUG
    bool xPowerOf2 = static_cast<int>(totalSize.X) % 2 == 0;
    bool yPowerOf2 = static_cast<int>(totalSize.Y) % 2 == 0;
    bool zPowerOf2 = static_cast<int>(totalSize.Z) % 2 == 0;
    VERIFY(xPowerOf2 && yPowerOf2 && zPowerOf2, "Max world size should be divisible by 2 to avoid floating errors");
#endif
    return OctTreeNode(ecs, totalSize);
}
} // namespace Collision
} // namespace Application