#pragma once

#include "Core/Headers/ListDefs.h"
#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"
#include "Core/Functionality/Headers/Event.h"

using namespace Core;
using namespace Core::Functionality;

namespace Application
{
	namespace Geometric
	{
		struct ContentBase;

		// generic class that can be inherited from for anything that needs to be stored inside a node
		struct ContainerBase
		{
			Event<> ContainerDeleted;

			ContainerBase();

			virtual ~ContainerBase();

			virtual void Update(Second dt);

			template <typename T, typename ...Ts>
			Ptr<ContentBase> AddContent(Ts ...args)
			{
				return AddContent(MakeUnique<T>(Forward<Ts>(args)...));
			}

			virtual Ptr<ContentBase> AddContent(UniquePtr<ContentBase> newContent);
			void RemoveContent(Ptr<ContentBase> content);
			bool HasContent(Ptr<ContentBase> content);

		protected:
			List<UniquePtr<ContentBase>> Content;
		};
	}
}