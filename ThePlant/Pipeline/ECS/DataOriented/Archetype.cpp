#include "Pipeline/ECS/DataOriented/Archetype.h"

namespace Application {
Archetype::Archetype(Archetype&& other)
: _id(std::move(other._id))
, _types(std::move(other._types))
, _entities(std::move(other._entities))
, _components(std::move(other._components))
{}

Archetype& Archetype::operator=(Archetype&& other)
{
    _id = std::move(other._id);
    _types = std::move(other._types);
    _entities = std::move(other._entities);
    _components = std::move(other._components);

    return *this;
}

Entity Archetype::AddEntity()
{
    Entity newEntity(GetId());

    _AddEntity(newEntity);
    
    return newEntity;
}

void Archetype::TransferEntityTo(Entity& entity, Archetype& destination)
{
    destination._AddEntity(entity);
    for (auto & component : _components)
    {
        if (!destination.HasComponent(component.first))
        {
            continue;
        }
        component.second->MoveEntityTo(_GetEntityIndex(entity.GetEntityId()), *(destination._components[component.first])); // this removes the entity from 'component'
    }
    
    entity._SetArchetypeId(destination.GetId());
}

bool Archetype::HasEntity(const EntityId& entity) const
{
    for (size_t index = 0; index < _entities.size(); ++index)
    {
        if (_entities[index] == entity)
        {
            return true;
        }
    }

    return false;
}

void Archetype::RemoveEntity(const Entity& entity)
{
    size_t entityIndex = _GetEntityIndex(entity.GetEntityId());
    for (auto& component : _components)
    {
        component.second->RemoveComponentAt(entityIndex);
    }
    _entities.erase(_entities.begin() + entityIndex);
}

const std::vector<EntityId>& Archetype::GetEntities() const
{
    return _entities;
}

bool Archetype::HasComponent(const Core::runtimeId_t& componentId) const
{
    return _components.find(componentId) != _components.end();
}

bool Archetype::ContainsTypes(const TypeCollection& types) const
{
    const std::vector<Core::runtimeId_t>& typeIds = types.Types();

    for (const Core::runtimeId_t& typeId : typeIds)
    {
        if (_components.find(typeId) == _components.end())
        {
            return false;
        }
    }

    return true;
}

bool Archetype::IsArchetype(const TypeCollection& types) const
{
    return _types == types;
}

const ArchetypeId& Archetype::GetId() const { return _id; }
const TypeCollection& Archetype::GetArchetype() const { return _types; }

Archetype::Archetype(Constructor, const Core::IncrementalId& id, const TypeCollection& types, std::vector<std::unique_ptr<IComponentList>>&& components)
: _id(id)
, _types(types)
{
    for (auto& component : components)
    {
        _components.emplace(component->ComponentType(), std::move(component));
    }
}

void Archetype::_AddEntity(const Entity& entity)
{
    _entities.emplace_back(entity.GetEntityId());
    for (auto& component : _components)
    {
        component.second->AddComponent();
    }
}
}// namespace Application