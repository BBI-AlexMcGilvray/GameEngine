#pragma once

#include "Core/Headers/ListDefs.h"
#include "Core/Headers/PtrDefs.h"

namespace Core
{
	namespace Functionality
	{
		// base set up for (essentially) entity-component system
		/*
		template <typename T>
		struct Subscription;

		template <typename T>
		struct Subscriber
		{
			Ptr<Subscription<T>> Subscription;

			Subscriber()
				: Subscription(nullptr)
			{}

			Subscriber(Ptr<T> object)
				: Subscription(object)
			{}

			~Subscriber()
			{
				EndSubscription();
			}

			void SubscribeTo(Ptr<Subscription<T>> subscription)
			{
				Subscription = subscription;
				Subscription->AddSubscriber(this);
			}

			void EndSubscription()
			{
				if (Subscription != nullptr)
				{
					Subscription->RemoveSubscriber(this);
					Subscription = nullptr;
				}
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
					subscriber->EndSubscription();
				}
			}

			void AddSubscriber(Ptr<Subscriber<T>> newSubscriber)
			{
				Push(Subscribers, newSubscriber);
			}

			void RemoveSubscriber(Ptr<Subscriber<T>> currentSubscriber)
			{
				Remove(Subscribers, currentSubscriber);
			}
		};

		template <typename T>
		struct SelfSubscriber : Subscriber<T>, Subscription<T>
		{};
		*/
	}
}