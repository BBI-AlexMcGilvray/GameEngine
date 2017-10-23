#pragma once

#include "Core/Headers/AllCore.h"

#include "Delegate.h"

namespace Core
{
	namespace Functionality
	{
		template <typename rT, typename Ts...>
		struct Event
		{
			EventBase()
			{}

			~EventBase()
			{
				for (auto& subscribee : Subscribees)
				{
					subscribee->EventParent = nullptr;
					UnSubscribe(subscribee);
				}
			}

			void operator()(Ts&&... args)
			{
				for (auto& subscribee : Subscribees)
				{
					subscribee(std::forward<Ts>(args)...);
				}
			}

			bool Subscribe(SharedPtr<Delegate<rT, Ts...>> newDelegate)
			{
				Push(Subscribees, newDelegate);

				return true;
			}

			bool UnSubscribe(SharedPtr<Delegate<rT, Ts...>> currentDelegate)
			{
				return Remove(Subscribees, currentDelegate);
			}

		private:
			List<SharedPtr<Delegate<rT, Ts...>>> Subscribees;
		};
	}
}