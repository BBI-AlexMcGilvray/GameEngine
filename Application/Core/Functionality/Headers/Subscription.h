#pragma once

#include "Core/Headers/ListDefs.h"
#include "Core/Headers/PtrDefs.h"

namespace Core
{
	namespace Functionality
	{
		// base set up for (essentially) entity-component system

		struct Subscription;

		struct Subscriber
		{
			Subscriber();
			Subscriber(Ptr<Subscription> subscription);

			virtual ~Subscriber();

			virtual void OnSubscription(Ptr<Subscription> subscription);
			virtual void OnSubscriptionDeleted();

		private:
			Ptr<Subscription> SubscriptionHolder;
		};

		struct Subscription
		{
			~Subscription();

			void Subscribe(Ptr<Subscriber> newSubscribee);
			void Unsubscribe(Ptr<Subscriber> currentSubscribee);

		protected:
			List<Ptr<Subscriber>>  Subscribers;
		};
	}
}