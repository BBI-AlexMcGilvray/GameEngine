#pragma once

#include "Core/Headers/ListDefs.h"
#include "Core/Headers/PtrDefs.h"

namespace Core
{
	namespace Functionality
	{
		// template classes for subscription based elements

		struct Subscriber
		{
			virtual void OnSubscriptionDeleted();
		};

		struct Subscription
		{
			void Subscribe(SharedPtr<Subscriber> newSubscribee);
			void Unsubscribe(SharedPtr<Subscriber> currentSubscribee);

		protected:
			List<SharedPtr<Subscriber>>  Subscribers;
		};
	}
}