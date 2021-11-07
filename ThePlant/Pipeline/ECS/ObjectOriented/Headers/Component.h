#pragma once

#include "Core/Headers/Hash.h"
#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"
#include "Core/Functionality/Headers/Event.h"

namespace Application {
struct EntityBase;

/*
We may need the concept of a 'control block' for components/component ptrs so that
we do not need to worry about copying over events for deletion (they all refere to the same control block that knows if the component is null or not)

Means Components would have a ptr to their control block and a 'GetComponentPtr' method to create a component ptr that references the control block
Then component ptrs have no default contructor so they can only be made with reference to the above control block

What about efficiency? this seems gross, to create all these shared ptrs floating around - maybe care about this later?
*/

class ComponentControlBlock;
template <typename T>
struct ComponentPtr;

struct IComponent
{
  // components should get created only once
  // since components reference the 'actual component' that is held elsewhere,
  // only one should exist and reference that 'actual compnent'
  IComponent(const IComponent&) = delete;
  IComponent& operator=(const IComponent&) = delete;
  IComponent& operator=(IComponent&&) = delete;

  Core::Functionality::Event<> Deleted;

  IComponent(EntityBase& entity);
  IComponent(IComponent&& other);

  virtual ~IComponent();

  virtual Core::Hash ComponentHash() const = 0;

  Core::Ptr<EntityBase> GetEntity() const;

  void SetActive(bool active = true);
  bool IsActive() const;

  void DeleteComponent();
  bool ShouldBeDeleted() const;

  // components are just a way to link to the system they are a part of
  // only entities should update, it is a way to have entity-specific logic like unity's monobehaviours
  // HOWEVER, this should be avoided in favour of components and systems
  virtual void Initialize();
  virtual void CleanUp();

private:
  bool _active = true;
  bool _delete = false;

  Core::Functionality::Delegate<> _entityDestroyed;
  Core::Ptr<EntityBase> _entity;

  std::shared_ptr<ComponentControlBlock> _controlBlock = nullptr;

  template<typename T>
  friend struct ComponentPtr;
  std::shared_ptr<ComponentControlBlock> GetControlBlock();
};

// should this be less of a class to inherit from, and more of a class that wraps other classes so that their life span is tied to an entity?
// not sure how that would fully work, maybe they are the same?
// Either way we need some way to get the actual component...
template<typename T>
struct Component : IComponent
{
  Component(EntityBase& entity, Core::Ptr<T> actualComponent)
    : IComponent(entity)
    , _actualComponent(actualComponent)
  {}

  Core::Hash ComponentHash() const final
  {
    return T::ClassHash();
  }

  static Core::Hash ClassHash()
  {
    return T::ClassHash();
  }

  Core::Ptr<T> operator->() const
  {
    return _actualComponent;
  }

private:
  Core::Ptr<T> _actualComponent; // actual components exist within the systems in Object-Oriented ECS
};

// should this inherit/templatize a base 'ControlBlock' type?
class ComponentControlBlock
{
public:
  ComponentControlBlock() = delete;
  ComponentControlBlock(const ComponentControlBlock&) = delete;
  ComponentControlBlock(ComponentControlBlock&&) = delete;
  ComponentControlBlock& operator=(const ComponentControlBlock&) = delete;
  ComponentControlBlock& operator=(ComponentControlBlock&&) = delete;

  ComponentControlBlock(IComponent& component)
  : _component(&component)
  , _componentDeleted([this]() mutable {
      this->_component = nullptr;

      return false;
    })
  {
    _component->Deleted += _componentDeleted;
  }

  ~ComponentControlBlock()
  {
    if (_component)
    {
      _component->Deleted -= _componentDeleted;
    }
  }

  const Core::Ptr<IComponent> get() const
  {
    return _component;
  }

  bool IsValid() const
  {
    return (_component != nullptr);
  }

  operator bool() const
  {
    return IsValid();
  }

private:
  Core::Ptr<IComponent> _component;
  Core::Functionality::Delegate<> _componentDeleted;
};
}// namespace Application