#include "Core/Functionality/Headers/Subscription.h"

namespace Core
{
	namespace Functionality
	{

		void Subscriber::OnSubscriptionDeleted()
		{
			// do nothing by default
		}

		void Subscription::Subscribe(SharedPtr<Subscriber> newSubscriber)
		{
			Push(Subscribers, newSubscriber);
		}

		void Subscription::Unsubscribe(SharedPtr<Subscriber> currentSubscriber)
		{
			Remove(Subscribers, currentSubscriber);
		}
	}
}