#pragma once

#include "Core/Headers/CoreDefs.h"

#include "Core/Headers/TimeDefs.h"

using namespace Core;

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

			virtual Second Update();

			Second GetDeltaTime();
			Second GetTimeSpan();

		private:
			SteadyClock Clock;
		};

		/*
			Fixed time step time manager based on: https://gafferongames.com/post/fix_your_timestep/
		*/

		struct FixedStepTimeManager : TimeManager
		{
			Second MaxStepSize;

			FixedStepTimeManager(Second maxStepSize = Second(167.0f)); // 0.0167 is 1 frame if we do 60 frames per second (or 167 milliseconds)

			Second Update() override;

			Second GetAccumulatedTime();

		private:
			Second Accumulator = 0_s;
		};
	}
}