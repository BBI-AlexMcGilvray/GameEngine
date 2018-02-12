#pragma once

#include "InputEvent.h"

#include "Core/Headers/PtrDefs.h"

namespace Application
{
	namespace Input
	{
		struct InputReceiverBase
		{
			InputReceiverBase();

			void Initialize();
			void CleanUp();

			virtual void HandleInput(SharedPtr<InputEventBase> event) = 0;
		};
	}
}