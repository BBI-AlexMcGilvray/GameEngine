#pragma once

#include <unordered_map>
#include <utility>

#include "Pipeline/ECS/ObjectOriented/Headers/Component.h"
#include "Pipeline/ECS/ObjectOriented/Headers/ComponentPtr.h"

#include "Core/Logging/LogFunctions.h"

#include "Core/Headers/Hash.h"
#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

#include "Core/Functionality/Headers/Event.h"

namespace Application {
struct State;

struct EntityBase
{
  Core::Functionality::Event<> OnDestroyed;

  EntityBase(const Core::Ptr<State> owningState);
  virtual ~EntityBase();

  template<typename T, typename... Ts>//, Templates::is_component<T>>
  ComponentPtr<T> AddComponent(Ts &&...args)
  {
    return AddComponent<T>(Core::MakeUnique<T>(*this, std::forward<Ts>(args)...));
  }

  template<typename T>//, Templates::is_component<T>>
  ComponentPtr<T> AddComponent(Core::UniquePtr<T> component)
  {
    ComponentPtr<T> existingComponent = GetComponent<T>();
    if (existingComponent) {
      DEBUG_ERROR("Entity", "Can't have two of the same component!");
      return existingComponent;
    }

    Components.insert(std::make_pair(T::ClassHash(), move(component)));
    return GetComponent<T>();
  }

  template<typename T, typename... Ts>//, Templates::is_component<T>>
  ComponentPtr<T> AddComponentAndInitialize(Ts &&...args)
  {
    return AddComponentAndInitialize<T>(Core::MakeUnique<T>(*this, Forward<Ts>(args)...));
  }

  template<typename T>//, Templates::is_component<T>>
  ComponentPtr<T> AddComponentAndInitialize(Core::UniquePtr<T> component)
  {
    ComponentPtr<T> existingComponent = GetComponent<T>();
    if (existingComponent) {
      DEBUG_ERROR("Entity", "Can't have two of the same component!");
      return existingComponent;
    } else {
      // this means a new component is created, so initialize it
      component->Initialize();
    }

    Components.insert(std::make_pair(T::ClassHash(), move(component)));
    return GetComponent<T>();
  }

  template<typename T>//, Templates::is_component<T>>
  void RemoveComponent()
  {
    Components.erase(T::ClashHash());
  }

  template<typename T>//, Templates::is_component<T>>
  bool HasComponent()
  {
    return (Components.find(T::ClassHash()) != Components.end());
  }

  // Change this to return ComponentPtr<T>
  template<typename T>//, Templates::is_component<T>>
  ComponentPtr<T> GetComponent()
  {
    if (!HasComponent<T>()) {
      return ComponentPtr<T>(nullptr);
    }

    return ComponentPtr<T>(static_cast<Core::Ptr<Component<T>>>(Components[T::ClassHash()].get()));
  }

  template<typename T>//, Templates::is_component<T>>
  void ClaimComponentFrom(Core::Ptr<EntityBase> entity)
  {
    entity->GiveComponentTo<T>(this);
  }

  template<typename T>//, Templates::is_component<T>>
  void GiveComponentTo(Core::Ptr<EntityBase> entity)
  {
    if (!HasComponent<T>()) {
      return;
    }

    entity->AddComponent<T>(Components[T::ClashHash()]);
  }

  virtual void Initialize();
  virtual void Start();
  virtual void Update(Core::Second dt);
  virtual void End();
  virtual void CleanUp();

protected:
  const Core::Ptr<State> _onwningState;

private:
  std::unordered_map<Core::Hash, Core::UniquePtr<IComponent>> Components;
};
}// namespace Application