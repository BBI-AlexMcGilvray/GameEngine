#pragma once

#include "Core/Debugging/Headers/Macros.h"

#include "Core/Headers/Hash.h"
#include "Core/Headers/MapDefs.h"
#include "Core/Headers/PtrDefs.h"

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

namespace Application
{
	struct ComponentBase;

	struct EntityBase
	{
		Core::Functionality::Event<> OnDestroyed;

		EntityBase() = default;
		virtual ~EntityBase();

		template <typename T, typename ...Ts>//, Templates::is_component<T>>
		Core::Ptr<Component> AddComponent(Ts ...args)
		{
			return AddComponent<T>(Core::MakeUnique<T>(this, Templates::Forward<Ts>(args)...));
		}

		template <typename T>//, Templates::is_component<T>>
		Core::Ptr<Component> AddComponent(Core::UniquePtr<T> component)
		{
			if (HasComponent<T>())
			{
				ALERT("Can't have two of the same component!");
				return;
			}

			Core::Insert(Components, T::ClassHash(), move(component));
			return Components[T::ClassHash()];
		}

		template <typename T>//, Templates::is_component<T>>
		void RemoveComponent()
		{
			Core::Erase(Components, T::ClashHash());
		}

		template <typename T>//, Templates::is_component<T>>
		bool HasComponent()
		{
			return Core::In(Components, T::ClassHash());
		}

		template <typename T>//, Templates::is_component<T>>
		Core::Ptr<Component> GetComponent()
		{
			if (!HasComponent<T>())
			{
				ALERT("Entity does not have component!");
				return nullptr;
			}

			return Components[T::ClashHash()];
		}

		template <typename T>//, Templates::is_component<T>>
		void ClaimComponentFrom(Core::Ptr<Entity> entity)
		{
			entity->GiveComponentTo<T>(this);
		}

		template <typename T>//, Templates::is_component<T>>
		void GiveComponentTo(Core::Ptr<Entity> entity)
		{
			if (!HasComponent<T>())
			{
				ALERT("Entity does not have component!");
				return;
			}

			entity->AddComponent<T>(Components[T::ClashHash()]);
		}

	private:
		Core::Map<Core::Hash, Core::UniquePtr<ComponentBase>> Components;
	};
}