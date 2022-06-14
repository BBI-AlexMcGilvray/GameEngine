#pragma once

#include "Core/Headers/BitmaskEnum.h"

#include "Pipeline/ECS/DataOriented/ECS.h"
#include "Pipeline/StateSystem/Headers/State.h"

#include "Pipeline/ECSSystems/ECSSystemUtils.h"

namespace Application {
using ECSSystemFlags = BitmaskEnum<ECSSystem>;

void SetSystemState(ECSSystemFlags& systems, const ECSSystem& system, const bool& active);
bool GetSystemState(const ECSSystemFlags& systems, const ECSSystem& system);
void SetECSSystems(State& state, const ECSSystemFlags& systems);
}// namespace Application