#include "Pipeline/ECS/DataOriented/Archetype.h"

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"

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

void Archetype::TransferEntityTo(const EntityId& entity, Archetype& destination)
{
    destination.AddEntity(entity);

    size_t entityIndex = _GetEntityIndex(entity);
    size_t destinationIndex = destination._GetEntityIndex(entity);
    for (auto & component : _components)
    {
        if (!destination.HasComponent(component.first))
        {
            component.second->RemoveComponentAt(entityIndex); // no component in new archetype means just toss component
            continue;
        }
        component.second->MoveEntityTo(entityIndex, *(destination._components[component.first]), destinationIndex); // this removes the entity from 'component'
    }
    _entities.erase(_entities.begin() + entityIndex);
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

void Archetype::AddEntity(const EntityId& entity)
{
    SCOPED_MEMORY_CATEGORY("ECS");
    _entities.emplace_back(entity);
    for (auto& component : _components)
    {
        component.second->AddComponent();
    }
}

void Archetype::RemoveEntity(const EntityId& entity)
{
    size_t entityIndex = _GetEntityIndex(entity);
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

Archetype::Archetype(Constructor, const ArchetypeInstanceId& id, const TypeCollection& types, std::vector<std::unique_ptr<IComponentList>>&& components)
: _id(id)
, _types(types)
{
    SCOPED_MEMORY_CATEGORY("ECS");
    for (auto& component : components)
    {
        _components.emplace(component->ComponentType(), std::move(component));
    }
#if DEBUG
    VERIFY(ContainsTypes(_types), "Archtypes must be created with all components for the listed types");
#endif
}

std::vector<std::unique_ptr<IComponentList>> Archetype::_GetComponentListCopies() const
{
    std::vector<std::unique_ptr<IComponentList>> copies;
    copies.reserve(_components.size());
    
    for (const auto& component : _components)
    {
        copies.push_back(component.second->CreateEmptyCopy());
    }

    return copies;
}
}// namespace Application