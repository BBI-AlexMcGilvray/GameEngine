#include "ApplicationManagement\Time\Headers\TimeManager.h"

namespace Application
{
	namespace Time
	{
		TimeManager::TimeManager()
		{
			InitialTime = Clock.now();

			PreviousTick = InitialTime;
			CurrentTick = InitialTime;
		}

		Second TimeManager::Update()
		{
			PreviousTick = CurrentTick;
			CurrentTick = Clock.now();

			return GetDeltaTime();
		}

		Second TimeManager::GetDeltaTime()
		{
			return (CurrentTick - PreviousTick);
		}

		Second TimeManager::GetTimeSpan()
		{
			return (CurrentTick - InitialTime);
		}

		// Fixed Time Step
		FixedStepTimeManager::FixedStepTimeManager(Second maxStepSize)
			: MaxStepSize(maxStepSize)
		{

		}

		Second FixedStepTimeManager::Update()
		{
			auto timePassed = TimeManager::Update();

			if (timePassed > MaxStepSize)
			{
				Accumulator += (timePassed - MaxStepSize);
				timePassed = MaxStepSize;
			}

			return timePassed;
		}

		Second FixedStepTimeManager::GetAccumulatedTime()
		{
			if (Accumulator > MaxStepSize)
			{
				Accumulator -= MaxStepSize;

				return MaxStepSize;
			}

			auto accumulatedTime = Accumulator;
			Accumulator = 0_s;

			return accumulatedTime;
		}
	}
}