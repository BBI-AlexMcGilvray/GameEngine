#pragma once

#include "Pipeline/AssetHandling/AssetLoaderFactory.h"
#include "Pipeline/Headers/ApplicationManager.h"

namespace Application {
struct ApplicationManager;

AssetLoaderFactory::AssetLoaderFactory(ApplicationManager& applicationManager)
: _applicationManager(applicationManager)
{}

void AssetLoaderFactory::LoadAsset(const Data::AssetName<void>& asset)
{
    _LoadAsset(asset, false);
}

void AssetLoaderFactory::LoadAndLockAsset(const Data::AssetName<void>& asset)
{
    _LoadAsset(asset, true);
}

void AssetLoaderFactory::_LoadAsset(const Data::AssetName<void>& asset, bool lock)
{
    // Note: we still need to verify that TemplateTypeAsString<T>() actually returns the right string...
    Create(asset.getType(), _applicationManager, asset);
}
}// namespace Application