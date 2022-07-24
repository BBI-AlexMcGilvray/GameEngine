#pragma once

#include <tuple>

#include "Core/Headers/type_traits.h"

#include "Pipeline/Input/Headers/InputStateTracker.h"

namespace Application {
namespace Input {
template <typename ...TRACKERS>
class InputState
{
public:
    using input_state_type = InputState<TRACKERS...>;

public:
    InputState()
    : _trackers(CreateTracker<TRACKERS>()...)
    {
        // static_assert(is_specialization_of<TRACKERS, InputStateTracker>::value, "The only types allowed are InputStateTrackers");
    }
    ~InputState() = default;

    template <typename STATE_TYPE, typename TRACKER_INPUT>
    const STATE_TYPE& GetState(const TRACKER_INPUT& input) const
    {
        const auto& tracker = std::get<type_index<TRACKER_INPUT, TRACKERS::input_type...>::value>(_trackers);
        return tracker.GetState(input);
    }

    template <typename STATE_TYPE, typename TRACKER_INPUT>
    void SetState(const TRACKER_INPUT& input, const STATE_TYPE& state)
    {
        auto& tracker = std::get<type_index<TRACKER_INPUT, TRACKERS::input_type...>::value>(_trackers);
        return tracker.SetState(input, state);
    }

private:
    std::tuple<TRACKERS...> _trackers;
};

// if we want to support having different/multiple trackers active, we will need a base class that they inherit from and handle knowing what state goes to what tracker
using MouseAndKeyboardState = InputState<MouseButtonTracker, MouseAxisTracker, KeyboardButtonTracker>;
// could have one for controllers that would be controller axis and controller buttons

}// namespace Input
}// namespace Application