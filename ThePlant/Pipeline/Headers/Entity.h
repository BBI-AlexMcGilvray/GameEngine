#pragma once

#include <unordered_map>

#include "Pipeline/Headers/Component.h"

#include "Core/Logging/Logger.h"

#include "Core/Headers/Hash.h"
#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

#include "Core/Functionality/Headers/Event.h"

/*
// Find out what is wrong with this before using it
namespace Templates
{
	template <typename T>
	struct is_component
	{
	private:
		template <typename T>
		static auto is_component_test() -> decltype(T::ClassHash(), IsBaseOf<Application::Component, T>, std::true_type);
		
		template <typename T>
		static auto is_component_test() -> decltype(std::false_type);

	public:
		static constexpr bool value = IsSame<std::true_type, decltype(is_component_test<T>())>::value;
	};
}
*/

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
    return AddComponent<T>(Core::MakeUnique<T>(this, Forward<Ts>(args)...));
  }

  template<typename T>//, Templates::is_component<T>>
  ComponentPtr<T> AddComponent(Core::UniquePtr<T> component)
  {
    ComponentPtr<T> existingComponent = GetComponent<T>();
    if (existingComponent) {
      DEBUG_ERROR("Entity", "Can't have two of the same component!");
      return existingComponent;
    }

    Components.insert(Core::MakePair(T::ClassHash(), move(component)));
    return GetComponent<T>();
  }

  template<typename T, typename... Ts>//, Templates::is_component<T>>
  ComponentPtr<T> AddComponentAndInitialize(Ts &&...args)
  {
    return AddComponentAndInitialize<T>(Core::MakeUnique<T>(this, Forward<Ts>(args)...));
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

    Components.insert(Core::MakePair(T::ClassHash(), move(component)));
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
  std::unordered_map<Core::Hash, Core::UniquePtr<ComponentBase>> Components;
};
}// namespace Application