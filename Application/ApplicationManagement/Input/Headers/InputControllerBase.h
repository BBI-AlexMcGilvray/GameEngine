#pragma once

#include "InputEvent.h"

#include "Core/Headers/PtrDefs.h"

#include "ApplicationManagement/Input/Headers/InputReceiverBase.h"

namespace Application
{
	namespace Input
	{
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