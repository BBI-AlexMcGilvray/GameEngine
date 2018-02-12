#pragma once

#include "InputEvent.h"

#include "Core/Headers/PtrDefs.h"

#include "ApplicationManagement/Input/Headers/InputReceiverBase.h"

namespace Application
{
	namespace Input
	{
		/*
		These controllers should take the input and map it to a specific action given some data.

		Then, that action is passed down to the receivers (starting with the focus, and moving on if it does not consume the input).
		*/
		struct InputControllerBase
		{
			InputControllerBase();

			void Initialize();
			void CleanUp();

			void SetFocus(SharedPtr<InputReceiverBase> focus);
			void ClearFocus();

			virtual void HandleInput(SharedPtr<InputEventBase> event) = 0;

		private:
			SharedPtr<InputReceiverBase> Focus;
			SharedPtr<InputReceiverBase> ParentReceiver;
		};
	}
}