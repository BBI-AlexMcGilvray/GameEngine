#include "Pipeline/Collision/OctTree.h"

#include "Core/Geometric/Functions.h"

#include "Core/Debugging/Profiling/Utils.h"

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

EntitySnapshot OctTreeNode::FindFirstEntity(const Core::Geometric::ShapeOrientation3D& shape) const
{
    Core::Geometric::AABBShapeOrientation3D boundedShape(shape);
    const OctTreeNode& containingNode = _FindContainingNode(shape);
    for (const auto& content : containingNode._content)
    {
        if (Core::Geometric::Intersect(content.boundCollider, boundedShape))
        {
            return _ecs.GetTemporaryEntitySnapshot(content.entity);
        }
    }

    // maybe we collide with a parent's content if we have a parent
    if (_parent == nullptr)
    {
        return EntitySnapshot();
    }
    return _parent->FindFirstEntity(shape);
}

std::vector<EntitySnapshot> OctTreeNode::FindAllEntities(const Core::Geometric::ShapeOrientation3D& shape) const
{
    DEBUG_PROFILE_SCOPE("OctTreeNode::FindAllEntities");

    std::vector<EntitySnapshot> entities;
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
            if (child->ContainsEntity(entity, checkChildren))
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
    // auto& container = _FindContainingNode(content.boundCollider);
    // if (container.ContainsEntity(content.entity, false))
    // {
    //     return;
    // }

    // container.AddContent(content);

    // it is currently faster to just re-add the content to non-destroyed nodes rather than check for existance.
    // likely the fastest way to is to just call AddStaticContent once for each instance
    // but we need to a way to verify they are only added in once
    AddContent(content);
}

std::vector<Collision> OctTreeNode::AllCollisions() const
{
    DEBUG_PROFILE_SCOPE("OctTreeNode::AllCollisions");

    std::vector<IntermediaryCollision> intermediaryCollisions;
    _AllCollisions(intermediaryCollisions);
    return _CreateCollisions(intermediaryCollisions);
}

void OctTreeNode::ClearTree(bool clearStatics)
{
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
    if ( _ChildrenExist())
    {
        return;
    }

    const Core::Geometric::AABB childBounds(_this.shape.dimensions * 0.5f);
    const Core::Math::Float3 childOriginOffset = childBounds.dimensions * 0.5f;

    for (size_t i = 0; i < NUMBER_OF_CHILDREN; ++i)
    {
        Core::Math::Float3 childOrigin = _this.orientation.position;
        childOrigin.X += childOriginOffset.X * (i < 4 ? 1 : -1);
        childOrigin.Y += childOriginOffset.Y * (i < 2 || i > 5 ? 1 : -1);
        childOrigin.Z += childOriginOffset.Z * (i % 2 ? 1 : -1);

        _children[i] = std::make_unique<OctTree_Constructor>(_ecs, childOrigin, childBounds, this);
    }
}

bool OctTreeNode::_Engulfs(const Core::Geometric::AABBShapeOrientation3D& shape) const
{
    // we may want to take these 'double check' intersect calls and move them to a generic method
    // particularly to NOT use bounding boxes when the shapes don't warrant them (points, spheres)
    return Core::Geometric::Engulfs(_this, shape.boundingBox); // && Core::Geometric::Engulfs(Core::Geometric::RemoveAA(_this), shape.shapeOrientation); // don't need the second for this purpose
}

bool OctTreeNode::_Intersects(const Core::Geometric::AABBShapeOrientation3D& shape) const
{
    // we may want to take these 'double check' intersect calls and move them to a generic method
    // particularly to NOT use bounding boxes when the shapes don't warrant them (points, spheres)
    return Core::Geometric::Intersect(_this, shape.boundingBox);// && Core::Geometric::Intersect(Core::Geometric::RemoveAA(_this), shape.shapeOrientation); // don't need the second for this purpose
}

// must be tied with the above
OctTreeNode& OctTreeNode::_FindContainingNode(const Core::Geometric::AABBShapeOrientation3D& shape)
{
    // DEBUG_PROFILE_SCOPE("OctTreeNode::_FindContainingNode");

    if (!_ChildrenExist())
    {
        return *this;
    }

    for (auto& child : _children)
    {
        if (child->_Engulfs(shape))
        {
            return child->_FindContainingNode(shape);
        }
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

    Core::Ptr<OctTreeNode> onlyContaining = nullptr;
    for (auto& child : _children)
    {
        if (child->_Engulfs(shape))
        {
            return child->_FindContainingNode(shape);
        }
    }

    return *this;
}

void OctTreeNode::_InsertContent(const OctTreeContent& content)
{
    // DEBUG_PROFILE_SCOPE("OctTreeNode::_InsertContent");

    if (_content.empty() && !_ChildrenExist())
    {
        _StopGapContent(content);
        return;
    }

    _CreateChildren();

    if (_stopGapped)
    {
        _RemoveStopGap();
    }
    // insert the new content
    auto& newContentContainer = _FindContainingNode(content.boundCollider);
    if (&newContentContainer == this)
    {
        _content.push_back(content);
        return;
    }
    newContentContainer._InsertContent(content);
}

void OctTreeNode::_StopGapContent(const OctTreeContent& content)
{
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

void OctTreeNode::_FindAllEntities(std::vector<EntitySnapshot>& entities, const Core::Geometric::AABBShapeOrientation3D& shape) const
{
    // DEBUG_PROFILE_SCOPE("OctTreeNode::_FindAllEntities");

    _InternalEntities(entities, shape);

    if (!_ChildrenExist())
    {
        return;
    }

    for (const auto& child : _children)
    {
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
        else if (Core::Geometric::Intersect(shape.boundingBox, child->_this))
        {
            child->_FindAllEntities(entities, shape);
        }
    }
}

void OctTreeNode::_InternalEntities(std::vector<EntitySnapshot>& entities, const Core::Geometric::AABBShapeOrientation3D& shape) const
{
    // DEBUG_PROFILE_SCOPE("OctTreeNode::_InternalEntities");

    for (const auto& content : _content)
    {
        // we may want to take these 'double check' intersect calls and move them to a generic method
        // particularly to NOT use bounding boxes when the shapes don't warrant them (points, spheres)
        if (Core::Geometric::Intersect(content.boundCollider, shape))
        {
            entities.push_back(_ecs.GetTemporaryEntitySnapshot(content.entity));
        }
    }
}

void OctTreeNode::_EntitiesForAllContent(std::vector<EntitySnapshot>& entities) const
{
    // DEBUG_PROFILE_SCOPE("OctTreeNode::_EntitiesForAllContent");

    for (const auto& content : _content)
    {
        entities.push_back(_ecs.GetTemporaryEntitySnapshot(content.entity));
    }

    if (!_ChildrenExist())
    {
        return;
    }

    for (const auto& child : _children)
    {
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
    // DEBUG_PROFILE_SCOPE("OctTreeNode::_InternalCollisions");

    // edge case covering due to _content.size() - 1 in loop
    if (_content.size() == 0)
    {
        return;
    }

    for (size_t i = 0; i < _content.size() - 1; ++i)
    {
        for (size_t j = i + 1; j < _content.size(); ++j)
        {
            // we may want to take these 'double check' intersect calls and move them to a generic method
            // particularly to NOT use bounding boxes when the shapes don't warrant them (points, spheres)
            if (Core::Geometric::Intersect(_content[i].boundCollider, _content[j].boundCollider))
            {
                collisions.push_back(IntermediaryCollision(_content[i].entity, _content[j].entity));
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

    for (size_t i = 0; i < _content.size(); ++i)
    {
        for (const auto& child : _children)
        {
            if (child->_content.empty())
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

            if (Core::Geometric::Intersect(_content[i].boundCollider.boundingBox, child->_this))
            {
                child->_FindAllCollisions(collisions, _content[i]);
            }
        }
    }
}

void OctTreeNode::_CollisionsWithAllContent(std::vector<IntermediaryCollision>& collisions, const OctTreeContent& content) const
{
    // DEBUG_PROFILE_SCOPE("OctTreeNode::_CollisionsWithAllContent");

    for (const auto& c : _content)
    {
        collisions.push_back(IntermediaryCollision(c.entity, content.entity));
    }

    if (!_ChildrenExist())
    {
        return;
    }

    for (const auto& child : _children)
    {
        child->_CollisionsWithAllContent(collisions, content);
    }
}

void OctTreeNode::_FindAllCollisions(std::vector<IntermediaryCollision>& collisions, const OctTreeContent& content) const
{
    // DEBUG_PROFILE_SCOPE("OctTreeNode::_FindAllCollisions");

    for (const auto& c : _content)
    {
        // we may want to take these 'double check' intersect calls and move them to a generic method
        // particularly to NOT use bounding boxes when the shapes don't warrant them (points, spheres)
        if (Core::Geometric::Intersect(c.boundCollider, content.boundCollider))
        {
            collisions.push_back(IntermediaryCollision(c.entity, content.entity));
        }
    }

    if (!_ChildrenExist())
    {
        return;
    }

    for (const auto& child : _children)
    {
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
        else if (Core::Geometric::Intersect(content.boundCollider.boundingBox, child->_this))
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
        //         if (Core::Geometric::Intersect(content.boundCollider.shapeOrientation, childShape))
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
        child->_AllCollisions(collisions);
    }
}

std::vector<Collision> OctTreeNode::_CreateCollisions(const std::vector<IntermediaryCollision>& intermediaryCollisions) const
{
    // DEBUG_PROFILE_SCOPE("OctTreeNode::_CreateCollisions");
    
    // this is to avoid creating multiple snapshots of the same entity
    // maybe we shouldn't do it? would need to be measured/timed
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
        collisions.emplace_back<Collision>({ snapshots[intermediaryCollision.entity1], snapshots[intermediaryCollision.entity2] });
    }
    
    return collisions;
}

bool OctTreeNode::_ClearNode(bool clearStatics)
{
    bool canDelete = true;

    if (_ChildrenExist())
    {
        for (auto& child : _children)
        {
            canDelete &= child->_ClearNode(clearStatics);
        }
        if (canDelete)
        {
            _children = { nullptr };
        }
    }

    bool containsStatic = false;
    if (_content.size() > 0)
    {
        for (size_t index = _content.size(); index > 0; --index)
        {
            size_t trueIndex = index - 1;
            const auto& content = _content[trueIndex];
            // if (!content.isStatic || clearStatics)
            {
                containsStatic = content.isStatic;
                _content.erase(_content.begin() + trueIndex);
            }
        }
    }
    canDelete &= containsStatic;
    
    canDelete &= _content.empty();
    if (canDelete)
    {
        _stopGapped = false;
    }

    return canDelete;
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

    return totalCount;
}

const std::vector<Core::Geometric::ShapeOrientation3D> OctTreeNode::_DEBUG_AllChildShapes() const
{
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