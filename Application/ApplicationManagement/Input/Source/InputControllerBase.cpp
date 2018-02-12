#pragma once

#include "ApplicationManagement/Input/Headers/InputControllerBase.h"

namespace Application
{
	namespace Input
	{
		InputControllerBase::InputControllerBase()
		{

		}

		void InputControllerBase::Initialize()
		{

		}

		void InputControllerBase::CleanUp()
		{

		}

		void InputControllerBase::SetFocus(SharedPtr<InputReceiverBase> focus)
		{
			Focus = focus;
		}

		void InputControllerBase::ClearFocus()
		{
			SetFocus(nullptr);
		}
	}
}