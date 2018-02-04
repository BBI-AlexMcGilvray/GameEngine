#pragma once

#include "Core/Debugging/Headers/Macros.h"

namespace Core
{
	namespace Functionality
	{
		struct LockerBase
		{
			void Lock()
			{
				LockCount++;
			}

			bool Unlock()
			{
				LockCount--;

				return IsLocked();
			}

			bool IsLocked()
			{
				MESSAGE(LockCount > 0, "LOCK COUNT DROPPING BELOW 0");
				return (LockCount > 0);
			}

		private:
			int LockCount = 0;
		};
	}
}