#include "ApplicationManagement/Headers/Component.h"

#include "ApplicationManagement/Headers/Entity.h"

using namespace Core;

namespace Application {
ComponentBase::ComponentBase(Ptr<EntityBase> entity)
  : ParentEntity(entity), OnEntityDestroyed([this]() {
      SetActive(false);
      DeleteComponent();

      return false;
    })
{
  // can't initialize here as the derived class won't be instantiated
}

ComponentBase::~ComponentBase()
{
  Deleted();
}

Ptr<EntityBase> ComponentBase::GetEntity() const
{
  return ParentEntity;
}

void ComponentBase::SetActive(bool active)
{
  Active = active;
}

bool ComponentBase::IsActive() const
{
  return Active;
}

void ComponentBase::DeleteComponent()
{
  Delete = true;
}

bool ComponentBase::ShouldBeDeleted() const
{
  return Delete;
}

void ComponentBase::Initialize()
{
  // nothing by default
}

void ComponentBase::CleanUp()
{
  // nothing by default
}
}// namespace Application