#pragma once

#include "Core/Headers/AllCore.h"

#include "Delegate.h"

namespace Core
{
	namespace Functionality
	{
		template <typename rT, typename Ts...>
		struct EventBase
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

			bool Subscribe(Ptr<Delegate<rT, Ts...>> newDelegate)
			{
				Push(Subscribees, newDelegate);

				return true;
			}

			bool UnSubscribe(Ptr<Delegate<rT, Ts...>> currentDelegate)
			{
				return Remove(Subscribees, currentDelegate);
			}

			operator bool()
			{
				return (Subscribees.size() != 0);
			}

		private:
			List<Ptr<Delegate<rT, Ts...>>> Subscribees;
		};

		template <typename ...Args>
		using Event<Args...> = EventBase<void, Args...>;
	}
}