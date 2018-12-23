#pragma once

#include "ApplicationManagement/Headers/Entity.h"

#include "Core/Headers/Hash.h"
#include "Core/Headers/MapDefs.h"
#include "Core/Headers/PtrDefs.h"
#include "Core/Functionality/Headers/Event.h"

namespace Application
{
	struct Component
	{
		Component(Core::Ptr<Entity> entity);

		virtual Core::Hash ClassHash() = 0;

		Core::Ptr<Entity> GetEntity();

	private:
		Core::Functionality::Delegate<> OnEntityDestroyed;
		Core::Ptr<Entity> Entity;
	};

	template <typename T>
	struct ComponentType : Component
	{
		Core::Hash ClassHash()
		{
			return T::ClashHash();
		}
	};
}