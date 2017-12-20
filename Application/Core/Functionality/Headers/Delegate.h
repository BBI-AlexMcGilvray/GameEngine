#pragma once

#include "Core/Headers/AllCore.h"
#include "Core/Headers/PtrDefs.h"

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
			DelegateBase(Ptr<FunctionBase<rT, Ts...>> function, Ptr<Event<rT, Ts...>> eventParent = nullptr)
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
			Ptr<Event<rT, Ts...>> EventParent;

		private:
			Ptr<FunctionBase<rT, Ts...>> DelegateFunction;

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