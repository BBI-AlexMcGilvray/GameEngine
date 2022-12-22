#pragma once

#include "Core/Headers/BitmaskEnum.h"

#include "Pipeline/Collision/CollisionManager.h"
#include "Pipeline/ECS/DataOriented/ECS.h"
#include "Pipeline/StateSystem/Headers/State.h"

#include "Pipeline/StateSystem/Headers/ECSSystemUtils.h"

namespace Application {
using ECSSystemFlags = BitmaskEnum<ECSSystem>;
using CollisionHandlerFlags = BitmaskEnum<CollisionHandler>;
using RenderLayerFlags = BitmaskEnum<RenderLayer>;

void SetSystemState(ECSSystemFlags& systems, const ECSSystem& system, const bool& active);
bool GetSystemState(const ECSSystemFlags& systems, const ECSSystem& system);
void SetECSSystems(State& state, const ECSSystemFlags& systems);

void SetCollisionHandlerState(CollisionHandlerFlags& handlers, const CollisionHandler& handler, const bool& active);
bool GetCollisionHandlerState(const CollisionHandlerFlags& handlers, const CollisionHandler& handler);
void SetCollisionHandlers(State& state, const CollisionHandlerFlags& handlers);

void SetRenderLayerState(RenderLayerFlags& layers, const RenderLayer& layer, const bool& active);
bool GetRenderLayerState(const RenderLayerFlags& layers, const RenderLayer& layer);
void SetRenderLayers(State& state, const RenderLayerFlags& layers);
}// namespace Application