#pragma once

#include "Core/Headers/ListDefs.h"
#include "Core/Headers/PtrDefs.h"

namespace Core
{
	namespace Functionality
	{
		// base set up for (essentially) entity-component system

		template <typename T>
		struct Subscription;

		template <typename T>
		struct Subscriber : SubscriberBase
		{
			Ptr<T> Object;

			Subscriber() = delete;

			Subscriber(Ptr<T> object)
				: Object(object)
			{}

			Subscriber(Ptr<T> object, Ptr<Subscription<T>> subscription)
				: SubscriberBase(subscription), Object(object)
			{}

			Subscriber(Ptr<Subscription<T>> subscription)
			{
				subscription->Subscribe(this);
			}

			~Subscriber()
			{
				if (SubscriptionHolder != nullptr)
				{
					SubscriptionHolder->Unsubscribe(this);
				}
			}

			void OnSubscription(Ptr<Subscriber> subscription)
			{
				SubscriptionHolder = subscription;
			}

			void OnSubscriptionDeleted()
			{
				SubscriptionHolder = nullptr;
			}
		};

		template <typename T>
		struct Subscription
		{
			List<Ptr<Subscriber<T>>>  Subscribers;

			~Subscription()
			{
				for (auto& subscriber : Subscribers)
				{
					subscriber->OnSubscriptionDeleted();
				}
			}

			void Subscribe(Ptr<Subscriber<T>> newSubscriber)
			{
				Push(Subscribers, newSubscriber);
				newSubscriber->OnSubscription(this);
			}

			void Unsubscribe(Ptr<Subscriber<T>> currentSubscriber)
			{
				Remove(Subscribers, currentSubscriber);
				currentSubscriber->OnSubscriptionDeleted();
			}
		};
	}
}