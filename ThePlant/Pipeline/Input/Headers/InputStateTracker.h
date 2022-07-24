#pragma once

#include <algorithm>

#include "Core/Headers/type_traits.h"
#include "Core/Headers/EnumUtils.h"
#include "Core/Math/Headers/Vector2.h"

#include "Pipeline/Input/Headers/InputDefs.h"

namespace Application {
namespace Input {
struct AxisState
{
    Core::Math::Int2 position; // current
    Core::Math::Int2 delta; // delta from LAST position
};

template <typename INPUT_TYPE, typename STATE_TYPE>
class InputStateTracker
{
public:
    using input_type = INPUT_TYPE;
    using state_type = STATE_TYPE;
    using tracker_type = InputStateTracker<input_type, state_type>;

public:
    const STATE_TYPE defaultState;

    InputStateTracker() = delete;

    InputStateTracker(STATE_TYPE&& defaultState)
    : defaultState(std::move(defaultState))
    {
        std::fill(_currentStates.begin(), _currentStates.end(), defaultState);
    }
    ~InputStateTracker() = default;

    InputStateTracker(InputStateTracker&&) = default;
    InputStateTracker& operator=(InputStateTracker&&) = default;

    InputStateTracker(const InputStateTracker&) = delete;
    InputStateTracker& operator=(const InputStateTracker&) = delete;

    const STATE_TYPE& GetState(const INPUT_TYPE& input) const
    {
        return _currentStates[Core::enum_cast(input)];
    }

    void SetState(const INPUT_TYPE& input, const STATE_TYPE& state)
    {
        _currentStates[Core::enum_cast(input)] = state;
    }

private:
    // make this an array and use the enum values as the index!
    Core::EnumIndexedArray<STATE_TYPE, INPUT_TYPE> _currentStates;
};

using MouseButtonTracker = InputStateTracker<MouseButton, ButtonState>; // mouse buttons are either up or down
using MouseAxisTracker = InputStateTracker<MouseAxis, AxisState>; // input axis have 2 directions (x, y)
using KeyboardButtonTracker = InputStateTracker<KeyboardButton, ButtonState>; // keyboard buttons are either up or down
// could have one for controller axis and buttons too

// create button state tracker
template <typename TRACKER>
auto CreateTracker() -> typename std::enable_if<std::is_same<typename TRACKER::state_type, ButtonState>::value, TRACKER>::type
{
    return TRACKER(ButtonState::Up);
}

// create mouse axis tracker
template <typename TRACKER>
auto CreateTracker() -> typename std::enable_if<std::is_same<typename TRACKER::state_type, AxisState>::value, TRACKER>::type
{
    return TRACKER(AxisState{});
}
}// namespace Input
}// namespace Application