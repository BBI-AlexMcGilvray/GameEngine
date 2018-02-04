#pragma once

#include "Core/Functionality/Headers/Function.h"
#include "Core/Functionality/Headers/LockerBase.h"

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/MapDefs.h"
#include "Core/Headers/TimeDefs.h"

namespace Core
{
	namespace Functionality
	{
		struct SchedulerBase : LockerBase
		{
			void Update(Second dt);

			void Add(VoidFunction<Second> func, Second key = 0_s);
			
		protected:
			// All scheduled functions, sorted by Second
			List<Pair<Second, VoidFunction<Second>>> ScheduledFunctions;

			virtual void Execute(VoidFunction<Second>& func, Second dt);
		};
	}
}