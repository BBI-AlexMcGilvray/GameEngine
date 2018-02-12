#pragma once

#include "InputEvent.h"

#include "Core/Headers/PtrDefs.h"

namespace Application
{
	namespace Input
	{
		/*
		These should take in some action and make a response - which will either consume, or pass along the input).
		*/
		struct InputReceiverBase
		{
			InputReceiverBase();

			void Initialize();
			void CleanUp();

			virtual void HandleInput(SharedPtr<InputEventBase> event) = 0;
		};
	}
}