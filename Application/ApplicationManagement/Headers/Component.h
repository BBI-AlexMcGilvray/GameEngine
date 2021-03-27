#pragma once

#include "Core/Headers/Hash.h"
#include "Core/Headers/MapDefs.h"
#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"
#include "Core/Functionality/Headers/Event.h"

namespace Application
{
	struct EntityBase;

	struct ComponentBase
	{
		Core::Functionality::Event<> Deleted;

		ComponentBase(Core::Ptr<EntityBase> entity);
		virtual ~ComponentBase();

		virtual Core::Hash ComponentHash() = 0;

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
		bool Active = true;
		bool Delete = false;

		Core::Functionality::Delegate<> OnEntityDestroyed;
		Core::Ptr<EntityBase> ParentEntity;
	};

	// should this be less of a class to inherit from, and more of a class that wraps other classes so that their life span is tied to an entity?
	// not sure how that would fully work, maybe they are the same?
	// Either way we need some way to get the actual component...
	template <typename T>
	struct Component : ComponentBase
	{
		Component(Core::Ptr<EntityBase> entity, Core::Ptr<T> actualComponent)
			: ComponentBase(entity)
			, ActualComponent(actualComponent)
		{}

		Core::Hash ComponentHash() final
		{
			return T::ClassHash();
		}

		static Core::Hash ClassHash()
		{
			return T::ClassHash();
		}

		Core::Ptr<T> operator->() const
		{
			return ActualComponent;
		}

	private:
		Core::Ptr<T> ActualComponent;
	};

	// to simplify holding a reference to a seperate component
	template <typename T>
	struct ComponentPtr
	{
		ComponentPtr(nullptr_t null)
			: ComponentPtr()
		{

		}

		ComponentPtr(Core::Ptr<ComponentBase> component)
			: ComponentPtr()
		{
			SetComponent(component);
		}

		ComponentPtr(Core::Ptr<Component<T>> component)
			: ComponentPtr()
		{
			SetComponent(component);
		}

		template <typename O>
		ComponentPtr(ComponentPtr<O> component)
			: ComponentPtr()
		{
			SetComponent(component);
		}

		ComponentPtr()
			: OnComponentDeleted([this]()
		{
			this->Component = nullptr;

			return false;
		})
			, Component(nullptr)
		{

		}

		void SetComponent(Core::Ptr<ComponentBase> component)
		{
			if (component->ClassHash() == T::ClassHash())
			{
				SetComponent(static_cast<Core::Ptr<Component<T>>>(component));
			}
			else
			{
				SetComponent(Core::Ptr<Component<T>(nullptr));
			}
		}

		void SetComponent(Core::Ptr<Component<T>> component)
		{
			if (component != Component && Component != nullptr)
			{
				Component->Deleted -= OnComponentDeleted;
			}

			Component = component;

			if (Component != nullptr)
			{
				Component->Deleted += OnComponentDeleted;
			}
		}

		Core::Ptr<Component<T>> GetComponent()
		{
			return Component;
		}

		ComponentPtr<T> operator=(Core::Ptr<ComponentBase> component)
		{
			SetComponent(component);
		}

		ComponentPtr<T> operator=(Core::Ptr<Component<T>> component)
		{
			SetComponent(component);
		}

		operator bool() const
		{
			return (Component != nullptr);
		}

		Component<T>& operator->() const
		{
			return *Component;
		}

	private:
		Core::Ptr<Component<T>> Component;

		Core::Functionality::Delegate<> OnComponentDeleted;
	};
}