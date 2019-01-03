#pragma once

#include "Core/Headers/Hash.h"
#include "Core/Headers/MapDefs.h"
#include "Core/Headers/PtrDefs.h"
#include "Core/Functionality/Headers/Event.h"

namespace Application
{
	struct EntityBase;

	struct ComponentBase
	{
		Core::Functionality::Event<> Deleted;

		ComponentBase(Core::Ptr<EntityBase> entity);
		virtual ~ComponentBase();

		Core::Ptr<EntityBase> GetEntity() const;

		void SetActive(bool active = true);
		bool IsActive() const;

		void DeleteComponent();
		bool ShouldBeDeleted() const;

		// need to determine if we need/want the below. I think we do so that we can handle state changes and have a nice place
		// to put things like getting access to other components and the like.
		// NOTE: presumably the entity would be in charge of handling things like this and when they get called
		virtual void Initialize();
		virtual void Start();
		virtual void Update();
		virtual void End();
		virtual void CleanUp();

		virtual void OnActiveChanged();

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
		Component(Core::Ptr<EntityBase> entity)
			: ComponentBase(entity)
		{}

		static Core::Hash ClassHash()
		{
			return T::ClassHash();
		}

	private:
		Core::Ptr<T> ActualComponent;
	};

	// to simplify holding a reference to a seperate component
	template <typename T>
	struct ComponentPtr
	{
		ComponentPtr(Core::Ptr<Component<T>> component = nullptr)
			: OnComponentDeleted([this]()
		{
			Component = nullptr;

			return false;
		})
		{
			SetComponent(component);
		}

		void SetComponent(Core::Ptr<Component<T>> component)
		{
			if (component != Component && Component != nullptr)
			{
				Component->Delete -= OnComponentDeleted;
			}

			Component = component;

			if (Component != nullptr)
			{
				Component->Delete += OnComponentDeleted;
			}
		}

		Core::Ptr<Component<T>> GetComponent()
		{
			return Component;
		}

		operator bool()
		{
			return (Component != nullptr);
		}

	private:
		Core::Ptr<Component<T>> Component;

		Core::Functionality::Delegate<> OnComponentDeleted;
	};
}