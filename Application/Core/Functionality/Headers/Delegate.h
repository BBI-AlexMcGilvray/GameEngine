#pragma once

#include "Core/Headers/AllCore.h"

#include "Function.h"

namespace Core
{
	namespace Functionality
	{
		template <typename rT, typename Ts...>
		struct Event;

		template <typename rT, typename Ts...>
		struct DelegateBase
		{
			DelegateBase(FunctionBase<rT, Ts...>* function, SharedPtr<Event<rT, Ts...>> eventParent = nullptr)
				: EventParent(eventParent)
				, DelegateFunction(function);
			{
				if (EventParent != nullptr)
				{
					EventParent->Subscribe(this);
				}
			}

			virtual ~DelegateBase()
			{
				if (EventParent != nullptr)
				{
					EventParent->Unsubscribe(this);
				}
			}

			rT operator()(Ts...args)
			{
				rT result = DelegateFunction(args...);

				ResultLogic(result);

				return result;
			}

		public:
			SharedPtr<Event<rT, Ts...>> EventParent;

		private:
			FunctionBase<rT, Ts...>* DelegateFunction;

			virtual void ResultLogic(rT result) = 0;
		};

		// standard subscription delegate
		template <typename Ts...>
		struct EventDelegate : DelegateBase<bool, Ts...>
		{
		private:
			void ResultLogic(bool result)
			{
				if (!result)
				{
					EventParent->Unsubscribe(this);
				}
			}
		};
	}
}