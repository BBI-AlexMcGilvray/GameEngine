#include "Core/Functionality/Headers/Subscription.h"

namespace Core
{
	namespace Functionality
	{
		Subscriber::Subscriber()
		{}

		Subscriber::Subscriber(Ptr<Subscription> subscription)
		{
			subscription->Subscribe(this);
		}

		Subscriber::~Subscriber()
		{
			if (SubscriptionHolder != nullptr)
			{
				SubscriptionHolder->Unsubscribe(this);
			}
		}

		void Subscriber::OnSubscription(Ptr<Subscription> subscription)
		{
			SubscriptionHolder = subscription;
		}

		void Subscriber::OnSubscriptionDeleted()
		{
			SubscriptionHolder = nullptr;
		}

		Subscription::~Subscription()
		{
			for (auto& subscriber : Subscribers)
			{
				subscriber->OnSubscriptionDeleted();
			}
		}

		void Subscription::Subscribe(Ptr<Subscriber> newSubscriber)
		{
			Push(Subscribers, newSubscriber);
			newSubscriber->OnSubscription(this);
		}

		void Subscription::Unsubscribe(Ptr<Subscriber> currentSubscriber)
		{
			Remove(Subscribers, currentSubscriber);
			currentSubscriber->OnSubscriptionDeleted();
		}

		void Subscription::Distribute()
		{
			for (auto& subscriber : Subscribers)
			{
				subscriber->Receive();
			}
		}
	}
}