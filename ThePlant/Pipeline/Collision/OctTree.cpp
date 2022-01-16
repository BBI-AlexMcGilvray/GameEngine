#include "Pipeline/Collision/OctTree.h"

namespace Application
{
namespace Collision
{
OctTreeNode::OctTreeNode(const Core::Math::Float3& totalSize)
: OctTree(Core::Math::Float3(0.0f), Core::Geometric::Box(totalSize))
{}

OctTreeNode::OctTreeNode(const Core::Math::Float3& origin, const Core::Geometric::Box box)
: _this{ Core::Geometric::Transform(origin), box }
{}

EntitySnapshot OctTreeNode::FindFirstEntity(const ShapeOrientation3D& shape) const
{
    OctTreeNode& containingNode = _FindContainingNode(shape);
    for (const auto& content : containingNode._content)
    {
        if (Intersect(content.shapeOrientation, shape))
        {
            return CreateSnapshot(content.entity);
        }
    }

    return CreateEmptySnapshot();
}

std::vector<EntitySnapshot> OctTreeNode::FindAllEntities(const ShapeOrientation3D& shape) const
{
    std::<EntitySnapshot> entities;
    // find the node that contains it first to limit the amount of searching we do
    OctTreeNode& containingNode = _FindContainingNode(shape);
    containingNode._FindAllEntities(entities, shape);
    return entities;
}

void OctTreeNode::AddContent(const OctTreeContent& content)
{
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
    _children.fill(nullptr);
    _content.clear();
    _stopGapped = false;
}

void OctTreeNode::_CreateChildren()
{
    if ( _ChildrenExist())
    {
        return;
    }

    for (size_t i = 0; i < 8; ++i)
    {
        _children[i] = std::make_unique<OctTreeNode>()
    }
}

bool OctTreeNode::_Engulfs(const ShapeOrientation3D& shape) const
{
    return Core::Geometric::Engulfs(_this, shape);
}

OctTreeNode& OctTreeNode::_FindContainingNode(const ShapeOrientation3D& shape) const
{
    if (!_ChildrenExist())
    {
        return *this;
    }

    for (auto& child : _children)
    {
        if (child._Engulfs(shape))
        {
            return child._FindContainingNode(shape);
        }
    }

    return *this;
}

void OctTreeNode::_InsertContent(const OctTreeContent& content)
{
    if (_content.empty() && !_ChildrenExist())
    {
        _content.insert(content);
        _stopGapped = true;
    }

    _CreateChildren();

    if (_stopGapped)
    {
        _stopGapped = false;
        _FindContainingNode(_stopGapped)._InsertContent(_content.pop_back()); // now that the tree has been expanded, try to move the stop-gapped content down a layer
    }
    _FindContainingNode(content.shapeOrientation)._content.push_back(content);
}

void OctTreeNode::_FindAllEntities(std::vector<EntitySnapshot>& entities, const ShapeOrientation& shape) const
{
    _InternalEntities(entities, shape);
    for (const auto& child : _children)
    {
        if (Engulfs(shape, child->_this))
        {
            child->_EntitiesForAllContent(collisions);
        }
        else if (Intersect(shape, child->_this))
        {
            child->_FindAllEntities(entities, shape);
        }
    }
}

void OctTreeNode::_InternalEntities(std::vector<EntitySnapshot>& entities, const ShapeOrientation& shape) const
{
    for (const auto& content : _content)
    {
        if (Intersect(content.shapeOrientation, shape))
        {
            entities.push_back(CreateEntitySnapshot(content.entity));
        }
    }
}

void OctTreeNode::_EntitiesForAllContent(std::vector<EntitySnapshot>& entities) const
{
    for (const auto& content : _content)
    {
        entities.push_back(CreateEntitySnapshot(content.entity));
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
    for (size_t i = 0; i < _content.size() - 1; ++i)
    {
        for (size_t j = i + 1; j < _content; ++j)
        {
            if (std::optional<Collision> collision = Intersect(_content[i].shapeOrientation, _content[j].shapeOrientation))
            {
                collisions.push_back(collision);
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
            if (Engulfs(_content[i].shapeOrientation, child->_this))
            {
                child->_CollisionsWithAllContent(collisions, _content[i]);
            }
            else if (Intersect(_content[i].shapeOrientation, child->_this))
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

    for (const auto& child : _children)
    {
        child->_CollisionsWithAllContent(collisions, content);
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
            snapshots[intermediaryCollision.entity1] = CreateSnapshot(intermediaryCollision.entity1);
        }
        if (snapshots.find(intermediaryCollision.entity2) == snapshots.end())
        {
            snapshots[intermediaryCollision.entity2] = CreateSnapshot(intermediaryCollision.entity2);
        }
    }

    std::vector<Collision> collisions;
    collisions.reserve(intermediaryCollisions);
    for (const auto& intermediaryCollision : intermediaryCollisions)
    {
        collisions.push_back({ snapshots[intermediaryCollision.entity1], snapshots[intermediaryCollision.entity2] });
    }
    
    return collisions;
}
} // namespace Collision
} // namespace Application