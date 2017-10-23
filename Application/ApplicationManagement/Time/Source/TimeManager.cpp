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

		Seconds TimeManager::Update()
		{
			PreviousTick = CurrentTick;
			CurrentTick = Clock.now();

			return GetDeltaTime();
		}

		Seconds TimeManager::GetDeltaTime()
		{
			return (CurrentTick - PreviousTick);
		}

		Seconds TimeManager::GetTimeSpan()
		{
			return (CurrentTick - InitialTime);
		}

		// Fixed Time Step
		FixedStepTimeManager::FixedStepTimeManager(Seconds maxStepSize)
			: MaxStepSize(maxStepSize)
		{

		}

		Seconds FixedStepTimeManager::Update()
		{
			auto timePassed = TimeManager::Update();

			if (timePassed > MaxStepSize)
			{
				Accumulator += (timePassed - MaxStepSize);
				timePassed = MaxStepSize;
			}

			return timePassed;
		}

		Seconds FixedStepTimeManager::GetAccumulatedTime()
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