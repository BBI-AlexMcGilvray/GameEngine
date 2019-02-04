#pragma once

#include "ApplicationManagement/Headers/Entity.h"

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"
#include "Core/Functionality/Headers/Event.h"

using namespace Core;
using namespace Core::Functionality;

namespace Application
{
	namespace Geometric
	{
		struct ContainerBase;

		// generic class that can be inherited from for anything that needs to be stored inside a node
		struct ContentBase : EntityBase
		{
			Event<> ContentDeleted;
			Delegate<> OnContainerDeleted;

			ContentBase();
			virtual ~ContentBase();

			void SetContainer(Ptr<ContainerBase> parentContainer);
			Ptr<ContainerBase> GetContainer() const;

		private:
			Ptr<ContainerBase> Container;
		};
	}
}