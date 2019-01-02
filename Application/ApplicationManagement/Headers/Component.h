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

	private:
		bool Active = true;
		bool Delete = false;

		Core::Functionality::Delegate<> OnEntityDestroyed;
		Core::Ptr<EntityBase> ParentEntity;
	};

	// should this be less of a class to inherit from, and more of a class that wraps other classes so that their life span is tied to an entity?
	// not sure how that would fully work, maybe they are the same?
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
	};

	//to simplify holding a reference to a component
	template <typename T>
	struct ComponentPtr
	{
		ComponentPtr(Core::Ptr<Component<T>> component = nullptr);

		void SetComponent(Core::Ptr<Component<T>> component);
		Core::Ptr<Component<T>> GetComponent();

	private:
		Core::Ptr<Component<T>> Component;

		Core::Functionality::Delegate<> OnComponentDeleted;
	};
}