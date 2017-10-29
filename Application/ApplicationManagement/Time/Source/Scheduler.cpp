#include "ApplicationManagement/Time/Headers/Scheduler.h"

namespace Application
{
	namespace Time
	{

		void SchedulerBase::Update(Second dt)
		{
			List<Pair<Second, VoidFunction<Second>>> CalledFunctions;
			for (auto& scheduledCall : ScheduledFunctions)
			{
				scheduledCall.first -= dt;

				if (scheduledCall.first <= 0_s)
				{
					// something wrong with the templates to get incorrect type matchup here
					Execute(scheduledCall.second, dt);
				}
			}
#pragma message("THIS NEEDS TO BE FIGURED OUT BEFORE SCHEDULERS ARE USED")
			//Remove<Pair<Second, Function<Second>>>(ScheduledFunctions, CalledFunctions);
		}

		void SchedulerBase::Add(VoidFunction<Second> func, Second key)
		{
			Push<Pair<Second, VoidFunction<Second>>>(ScheduledFunctions, Pair<Second, VoidFunction<Second>>(key, func));
		}

		void SchedulerBase::Execute(VoidFunction<Second> func, Second dt)
		{
			func(move(dt));
		}
	}
}