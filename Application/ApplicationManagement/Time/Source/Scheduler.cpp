#include "ApplicationManagement/Time/Headers/Scheduler.h"

namespace Application
{
	namespace Time
	{

		void SchedulerBase::Update(Second dt)
		{
			Execute(dt);
		}

		void SchedulerBase::Add(VoidFunction<Second> func, Second key)
		{
			Push<Pair<Second, VoidFunction<Second>>>(ScheduledFunctions, Pair<Second, VoidFunction<Second>>(key, func));
		}

		void SchedulerBase::Execute(Second dt)
		{
			for (auto& scheduledCall : ScheduledFunctions)
			{
				scheduledCall.first -= dt;

				if (scheduledCall.first <= 0_s)
				{
					// something wrong with the templates to get incorrect type matchup here
					//scheduledCall.second(dt);
				}
			}
		}
	}
}