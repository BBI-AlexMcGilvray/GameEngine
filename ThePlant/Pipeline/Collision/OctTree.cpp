#include "Pipeline/Collision/OctTree.h"

#include "Core/Geometric/Functions.h"

namespace Application
{
namespace Collision
{
struct OctTree_Constructor : public OctTreeNode
{
    OctTree_Constructor(ECS& ecs, const Core::Math::Float3& origin, const Core::Geometric::Box& box, const Core::Ptr<OctTreeNode> parent)
    : OctTreeNode(ecs, origin, box, parent)
    {}
};

OctTreeNode::OctTreeNode(ECS& ecs, const Core::Math::Float3& totalSize)
: OctTree(ecs, Core::Math::Float3(0.0f), Core::Geometric::Box(totalSize), nullptr)
{}

OctTreeNode::OctTreeNode(ECS& ecs, const Core::Math::Float3& origin, const Core::Geometric::Box& box, const Core::Ptr<OctTreeNode> parent)
: _ecs(ecs)
, _parent(parent)
, _this{ Core::Geometric::Transform(origin), box }
{}

EntitySnapshot OctTreeNode::FindFirstEntity(const Core::Geometric::ShapeOrientation3D& shape) const
{
    const OctTreeNode& containingNode = _FindContainingNode(shape);
    for (const auto& content : containingNode._content)
    {
        if (Core::Geometric::Intersect(content.shapeOrientation, shape))
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
    std::vector<EntitySnapshot> entities;
    // not calling '_FindContainingNode' because we want EVERYTHING it may intersect with, so we may as well start from the top
    _FindAllEntities(entities, shape);
    return entities;
}

void OctTreeNode::AddContent(const OctTreeContent& content)
{
#if DEBUG
    VERIFY(_parent != nullptr || _Engulfs(content.shapeOrientation));// All content should exist WITHIN the topmost node
#endif

    // debug logic to check if content already exists?
    _InsertContent(content);
}

std::vector<Collision> OctTreeNode::AllCollisions() const
{
    std::vector<IntermediaryCollision> intermediaryCollisions;
    _AllCollisions(intermediaryCollisions);
    return _CreateCollisions(intermediaryCollisions);
}

void OctTreeNode::ClearTree()
{
    _children = { nullptr }; // an efficiency may be to not clear the children, just progressively clear content (avoid constant allocations)
    _content.clear();
    _stopGapped = false;
}

#if DEBUG
const std::array<std::unique_ptr<OctTreeNode>, 8>& OctTreeNode::DEBUG_GetAllChildren() const
{
    return _children;
}

const Core::Geometric::ShapeOrientation<Core::Geometric::Box>& OctTreeNode::DEBUG_GetBounds() const
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

    const Core::Geometric::Box childBox(_this.shape.dimensions * 0.5f);
    const Core::Math::Float3 childOriginOffset = childBox.dimensions * 0.5f;

    for (size_t i = 0; i < NUMBER_OF_CHILDREN; ++i)
    {
        Core::Math::Float3 childOrigin = _this.orientation.GetPosition();
        childOrigin.X += childOriginOffset.X * (i < 4 ? 1 : -1);
        childOrigin.Y += childOriginOffset.Y * (i < 2 || i > 5 ? 1 : -1);
        childOrigin.Z += childOriginOffset.Z * (i % 2 ? 1 : -1);

        _children[i] = std::make_unique<OctTree_Constructor>(_ecs, childOrigin, childBox, this);
    }
}

bool OctTreeNode::_Engulfs(const Core::Geometric::ShapeOrientation3D& shape) const
{
    return Core::Geometric::Engulfs(_this, shape);
}

// must be tied with the above
OctTreeNode& OctTreeNode::_FindContainingNode(const Core::Geometric::ShapeOrientation3D& shape)
{
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
const OctTreeNode& OctTreeNode::_FindContainingNode(const Core::Geometric::ShapeOrientation3D& shape) const
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
    if (_content.empty() && !_ChildrenExist())
    {
        _content.push_back(content);
        _stopGapped = true;
        return;
    }

    _CreateChildren();

    if (_stopGapped)
    {
        _stopGapped = false;
        // get and remove the stop-gapped content so it can be properly insterted
        OctTreeContent stopGappedContent = _content.back();
        _content.pop_back();
        auto& stopGappedContainer = _FindContainingNode(stopGappedContent.shapeOrientation);
        stopGappedContainer._InsertContent(stopGappedContent); // now that the tree has been expanded, try to move the stop-gapped content down a layer
    }
    // insert the new content
    auto& newContentContainer = _FindContainingNode(content.shapeOrientation);
    if (&newContentContainer == this)
    {
        _content.push_back(content);
        return;
    }
    newContentContainer._InsertContent(content);
}

void OctTreeNode::_FindAllEntities(std::vector<EntitySnapshot>& entities, const Core::Geometric::ShapeOrientation3D& shape) const
{
    _InternalEntities(entities, shape);

    if (!_ChildrenExist())
    {
        return;
    }

    for (const auto& child : _children)
    {
        if (Core::Geometric::Engulfs(shape, child->_this))
        {
            child->_EntitiesForAllContent(entities);
        }
        else if (Core::Geometric::Intersect(shape, child->_this))
        {
            child->_FindAllEntities(entities, shape);
        }
    }
}

void OctTreeNode::_InternalEntities(std::vector<EntitySnapshot>& entities, const Core::Geometric::ShapeOrientation3D& shape) const
{
    for (const auto& content : _content)
    {
        if (Core::Geometric::Intersect(content.shapeOrientation, shape))
        {
            entities.push_back(_ecs.GetTemporaryEntitySnapshot(content.entity));
        }
    }
}

void OctTreeNode::_EntitiesForAllContent(std::vector<EntitySnapshot>& entities) const
{
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
    _InternalCollisions(collisions);
    _CollisionsWithChildren(collisions);
    _ChildCollisions(collisions);
}

void OctTreeNode::_InternalCollisions(std::vector<IntermediaryCollision>& collisions) const
{
    // edge case covering due to _content.size() - 1 in loop
    if (_content.size() == 0)
    {
        return;
    }

    for (size_t i = 0; i < _content.size() - 1; ++i)
    {
        for (size_t j = i + 1; j < _content.size(); ++j)
        {
            if (Core::Geometric::Intersect(_content[i].shapeOrientation, _content[j].shapeOrientation))
            {
                collisions.push_back(IntermediaryCollision(_content[i].entity, _content[j].entity));
            }
        }
    }
}

void OctTreeNode::_CollisionsWithChildren(std::vector<IntermediaryCollision>& collisions) const
{
    if (!_ChildrenExist())
    {
        return;
    }

    for (size_t i = 0; i < _content.size(); ++i)
    {
        for (const auto& child : _children)
        {
            if (Core::Geometric::Engulfs(_content[i].shapeOrientation, child->_this))
            {
                child->_CollisionsWithAllContent(collisions, _content[i]);
            }
            else if (Core::Geometric::Intersect(_content[i].shapeOrientation, child->_this))
            {
                child->_FindAllCollisions(collisions, _content[i]);
            }
        }
    }
}

void OctTreeNode::_CollisionsWithAllContent(std::vector<IntermediaryCollision>& collisions, const OctTreeContent& content) const
{
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
    for (const auto& c : _content)
    {
        if (Core::Geometric::Intersect(c.shapeOrientation, content.shapeOrientation))
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
        if (Core::Geometric::Engulfs(content.shapeOrientation, child->_this))
        {
            child->_CollisionsWithAllContent(collisions, content);
        }
        else if (Core::Geometric::Intersect(content.shapeOrientation, child->_this))
        {
            child->_FindAllCollisions(collisions, content);
        }
    }
}

void OctTreeNode::_ChildCollisions(std::vector<IntermediaryCollision>& collisions) const
{
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