#include "Pipeline/ECS/ObjectOriented/Headers/Component.h"

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"

#include "Pipeline/ECS/ObjectOriented/Headers/ComponentPtr.h"
#include "Pipeline/ECS/ObjectOriented/Headers/Entity.h"

using namespace Core;

namespace Application {
IComponent::IComponent(EntityBase& entity)
: _entity(&entity)
, _entityDestroyed([this]() {
    SetActive(false);
    DeleteComponent();

    return false;
  })
{
  _entity->OnDestroyed += _entityDestroyed;
}

IComponent::IComponent(IComponent&& other)
: _active(std::move(other._active))
, _delete(std::move(other._delete))
, _entity(std::move(other._entity))
, _controlBlock(std::move(other._controlBlock))
, _entityDestroyed([this]() {
    SetActive(false);
    DeleteComponent();

    return false;
  })
{
  _entity->OnDestroyed += _entityDestroyed;
}

IComponent::~IComponent()
{
  Deleted();
}

Ptr<EntityBase> IComponent::GetEntity() const
{
  return _entity;
}

void IComponent::SetActive(bool active)
{
  _active = active;
}

bool IComponent::IsActive() const
{
  return _active;
}

void IComponent::DeleteComponent()
{
  _delete = true;
}

bool IComponent::ShouldBeDeleted() const
{
  return _delete;
}

void IComponent::Initialize()
{
  // nothing by default
}

void IComponent::CleanUp()
{
  // nothing by default
}

std::shared_ptr<ComponentControlBlock> IComponent::GetControlBlock()
{
  SCOPED_MEMORY_CATEGORY("Component_OO");
  if (_controlBlock == nullptr)
  {
    _controlBlock = std::make_shared<ComponentControlBlock>(*this);
  }

  return _controlBlock;
}
}// namespace Application