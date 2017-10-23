#pragma once

#include "Core/Functionality/Headers/Function.h"

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/ListDefs.h"
#include "Core/Headers/TimeDefs.h"

using namespace Core;
using namespace Core::Functionality;

namespace Application
{
	namespace Time
	{
		/*
		struct SchedulerBase
		{
			void Update(Second dt);

		private:
			virtual void Execute() = 0;
		};

		template <typename Ts...>
		struct Scheduler : SchedulerBase
		{
		private:
			List<Function<Ts...>> ScheduledFunctions;
		};
		*/
	}
}