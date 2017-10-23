#pragma once

#include "Core/Headers/CoreDefs.h"

#include "Core/Headers/TimeDefs.h"

namespace Application
{
	namespace Time
	{
		struct TimeManager
		{
			TimePoint InitialTime;
			TimePoint PreviousTick;
			TimePoint CurrentTick;

			TimeManager();

			virtual Seconds Update();

			Seconds GetDeltaTime();
			Seconds GetTimeSpan();

		private:
			SteadyClock Clock;
		};

		/*
			Fixed time step time manager based on: https://gafferongames.com/post/fix_your_timestep/
		*/

		struct FixedStepTimeManager : TimeManager
		{
			Seconds MaxStepSize;

			FixedStepTimeManager(Seconds maxStepSize = 0.0167_s); // 0.0167 is 1 frame if we do 60 frames per second

			Seconds Update() override;

			Seconds GetAccumulatedTime();

		private:
			Seconds Accumulator = 0_s;
		};
	}
}