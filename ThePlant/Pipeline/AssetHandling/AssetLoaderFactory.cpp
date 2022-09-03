#pragma once

#include "Pipeline/AssetHandling/AssetLoaderFactory.h"
#include "Pipeline/Headers/ApplicationManager.h"
#include "Pipeline/StateSystem/Headers/State.h"

namespace Application {
struct ApplicationManager;

AssetLoaderFactory::AssetLoaderFactory(ApplicationManager& applicationManager)
: _applicationManager(applicationManager)
{}

void AssetLoaderFactory::LoadAsset(const Data::AssetName<void>& asset)
{
    _LoadAsset(_applicationManager.StateManager().GetActiveState(), asset, false);
}

void AssetLoaderFactory::LoadAsset(State& state, const Data::AssetName<void>& asset)
{
    _LoadAsset(state, asset, false);
}

void AssetLoaderFactory::LoadAndLockAsset(const Data::AssetName<void>& asset)
{
    _LoadAsset(_applicationManager.StateManager().GetActiveState(), asset, true);
}

void AssetLoaderFactory::LoadAndLockAsset(State& state, const Data::AssetName<void>& asset)
{
    _LoadAsset(state, asset, true);
}
void AssetLoaderFactory::_LoadAsset(State& state, const Data::AssetName<void>& asset, bool lock)
{
    // Note: we still need to verify that TemplateTypeAsString<T>() actually returns the right string...
    Create(asset.getType(), state, asset);
}
}// namespace Application