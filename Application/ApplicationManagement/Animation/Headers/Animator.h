#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

namespace Application
{
	namespace Animation
	{
		class IAnimator
		{
		public:
			virtual void Update(Core::Second dt) = 0;
		};
	}
}