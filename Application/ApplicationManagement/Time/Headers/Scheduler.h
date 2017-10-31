#pragma once

#include "Core/Functionality/Headers/Function.h"
#include "Core/Functionality/Headers/Lock.h"

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/MapDefs.h"
#include "Core/Headers/TimeDefs.h"

using namespace Core;
using namespace Core::Functionality;

namespace Application
{
	namespace Time
	{
		struct SchedulerBase : ILock
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