#pragma once

#include "Core/Headers/PtrDefs.h"

#include "Pipeline/ECS/ObjectOriented/Headers/Component.h"

namespace Application {
// to simplify holding a reference to a component
template<typename T>
struct ComponentPtr
{
  ComponentPtr()
  {
    SetComponent(nullptr);
  }

  ComponentPtr(nullptr_t null)
  : ComponentPtr()
  {}

  ComponentPtr(const Core::Ptr<IComponent>& component)
  {
    SetComponent(component);
  }

  ComponentPtr(const Core::Ptr<Component<T>>& component)
  {
    SetComponent(component);
  }

  ComponentPtr(const ComponentPtr& other)
  : _component(other._component)
  , _controlBlock(other._controlBlock)
  {}

  ComponentPtr(const ComponentPtr&& other)
  : _component(std::move(other._component))
  , _controlBlock(std::move(other._controlBlock))
  {}

  ComponentPtr& operator=(nullptr_t)
  {
    SetComponent(nullptr);
  }

  ComponentPtr& operator=(const Core::Ptr<IComponent>& component)
  {
    SetComponent(component);

    return *this;
  }

  ComponentPtr& operator=(const Core::Ptr<Component<T>>& component)
  {
    SetComponent(component);

    return *this;
  }

  ComponentPtr& operator=(const ComponentPtr<T>& other)
  {
    _component = other._component;
    _controlBlock = other._controlBlock;

    return *this;
  }

  ComponentPtr& operator=(ComponentPtr<T>&& other)
  {
    _component = std::move(other._component);
    _controlBlock = std::move(other._controlBlock);

    return *this;
  }

  void SetComponent(const Core::Ptr<IComponent>& component)
  {
    if (component == nullptr)
    {
      SetComponent(nullptr);
    }

    if (component->ClassHash() != T::ClassHash())
    {
      throw; // why are you trying to set a different component type
    }
    
    SetComponent(static_cast<Core::Ptr<Component<T>>>(component));
  }

  void SetComponent(const Core::Ptr<Component<T>>& component)
  {
    if (component == nullptr)
    {
      SetComponent(nullptr);
    }
    
    _component = component;
    _controlBlock = _component->GetControlBlock();
  }

  void SetComponent(nullptr_t)
  {
    _component = nullptr;
    _controlBlock = nullptr;
  }

  Core::Ptr<Component<T>> TryGetComponent()
  {
    if (!IsValid())
    {
      _component = nullptr;
    }
    
    return _component;
  }

  Core::Ptr<Component<T>> GetComponent() const
  {    
    return _component;
  }

  bool IsValid() const
  {
    return (_controlBlock != nullptr && _controlBlock->IsValid());
  }

  operator bool() const
  {
    return IsValid();
  }

  Component<T>& operator->() const
  {
    return *GetComponent();
  }

  Component<T>& operator*() const
  {
    return *GetComponent();
  }

private:
  Core::Ptr<Component<T>> _component;

  std::shared_ptr<ComponentControlBlock> _controlBlock = nullptr;  
};
}// namespace Application