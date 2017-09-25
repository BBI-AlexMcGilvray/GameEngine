#pragma once

#include "InputDefs.h"

namespace Input
{
	struct EventMetaData
	{
		uint Timestamp;
		uint WindowId;

		inline EventMetaData(uint timestamp, uint windowId)
			: Timestamp(timestamp), WindowId(windowId)
		{}
	};

// Mouse Event data
	struct MouseMetaData : EventMetaData
	{
		int MouseX;
		int MouseY;

		inline MouseMetaData(uint timestamp, uint windowId, int mouseX, int mouseY)
			: EventMetaData(timestamp, windowId), MouseX(mouseX), MouseY(mouseY)
		{}
	};

	struct MouseClickedData : MouseMetaData
	{
		MouseButton Button;
		ButtonState State;
		uint Clicks;

		inline MouseClickedData(uint timestamp, uint windowId, int mouseX, int mouseY, MouseButton button, ButtonState state, uint clicks)
			: MouseMetaData(timestamp, windowId, mouseX, mouseY), Button(button), State(state), Clicks(clicks)
		{}
	};

	struct MouseMovedData : MouseMetaData
	{
		int DeltaX;
		int DeltaY;

		inline MouseMovedData(uint timestamp, uint windowId, int mouseX, int mouseY, int deltaX, int deltaY)
			: MouseMetaData(timestamp, windowId, mouseX, mouseY), DeltaX(deltaX), DeltaY(deltaY)
		{}
	};

	struct MouseWheeledData : MouseMetaData
	{
		bool Forward;

		inline MouseWheeledData(uint timestamp, uint windowId, int mouseX, int mouseY, bool forward)
			: MouseMetaData(timestamp, windowId, mouseX, mouseY), Forward(forward)
		{}
	};

// Keyboard Event Data
	struct KeyboardButtonData : EventMetaData
	{
		KeyboardButton Button;
		ButtonState State;

		inline KeyboardButtonData(uint timestamp, uint windowId, KeyboardButton button, ButtonState state)
			: EventMetaData(timestamp, windowId), Button(button), State(state)
		{}
	};

	struct InputEventBase
	{
		virtual InputEventType GetInputEventType() const
		{
			return InputEventType::Undetermined;
		}
	};

	template <class D>
	struct InputEvent : InputEventBase
	{
		InputEventType Type;
		D Data;

		InputEvent(InputEventType type, D&& data)
			: Type(type), Data(move(data))
		{}

		template <class ...Ts>
		InputEvent(InputEventType type, Ts ...args)
			: Type(type), Data(std::forward<Ts>(args)...)
		{}

		inline InputEventType GetInputEventType() const
		{
			return Type;
		}
	};
}