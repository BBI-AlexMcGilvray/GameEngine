#include "Core/Functionality/Headers/Scheduler.h"

namespace Core
{
	namespace Functionality
	{
		void SchedulerBase::Update(Second dt)
		{
			List<int> calledIndices;

			int currentIndex = 0;
			for (auto& scheduledCall : ScheduledFunctions)
			{
				scheduledCall.first -= dt;

				if (!IsLocked() && scheduledCall.first <= 0_s)
				{
					// something wrong with the templates to get incorrect type matchup here
					Execute(scheduledCall.second, dt);
					Push(calledIndices, currentIndex);
				}
				currentIndex++;
			}

			RemoveIndex(ScheduledFunctions, calledIndices);
		}

		void SchedulerBase::Add(VoidFunction<Second> func, Second key)
		{
			Push<Pair<Second, VoidFunction<Second>>>(ScheduledFunctions, Pair<Second, VoidFunction<Second>>(key, func));
		}

		void SchedulerBase::Execute(VoidFunction<Second>& func, Second dt)
		{
			func(move(dt));
		}
	}
}