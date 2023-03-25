#include "Pipeline/Rendering/Headers/MaterialManager.h"

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"

#include "Pipeline/StateSystem/Headers/State.h"

using namespace Core;

namespace Application {
namespace Rendering {
  MaterialManager::MaterialManager(Data::AssetManager& assetManager, AssetLoaderFactory& assetLoaderFactory, ShaderManager& shaderManager)
  : _assetManager(assetManager)
  , _assetLoaderFactory(assetLoaderFactory)
  , _shaderManager(shaderManager)
  {
    _assetLoaderFactory.Register(Core::HashType<Data::Rendering::MaterialData>(), [&](State& state, const Data::AssetName<void>& asset)
    {
      AddMaterial(asset);
    });
  }

  MaterialManager::~MaterialManager()
  {
    _assetLoaderFactory.Unregister(Core::HashType<Data::Rendering::MaterialData>());

    // if we want to lock the shaders in the asset manager (which we shouldn't need to do - except in debug mode so we can live-edit them) then we should unlock them all here
  }

  void MaterialManager::Initialize()
  {
  }

  void MaterialManager::Start()
  {
  }

  void MaterialManager::Update(Second dt)
  {
    // this could be where we update the materials that require a time input
  }

  void MaterialManager::End()
  {
  }

  void MaterialManager::CleanUp()
  {
  }

  Core::instanceId<Material> MaterialManager::AddMaterial(const Data::AssetName<Data::Rendering::MaterialData>& material)
  {
    SCOPED_MEMORY_CATEGORY("Rendering");

    // should check if it exists and return the existing? this does mean that the same materials will share their parameters
    // NOTE: can't do this at the moment becaus materials do not know their AssetName to do the comparison -> should they?
    // if (auto iter = std::find(_materials.begin(), _materials.end(), material); iter != _materials.end())
    // {
    //   return iter->second;
    // }

    Core::instanceId<Material> newId = GetInstanceId<Material>();

    const auto materialData = _assetManager.getAssetData(material);
    _materials.emplace(std::make_pair(newId, CreateMaterial(materialData, _shaderManager)));

    return newId;
  }

  void MaterialManager::RemoveMaterial(const Core::instanceId<Material>& materialId)
  {
    _materials.erase(materialId);
  }

  Material& MaterialManager::GetDefaultMaterial()
  {
    if (!_defaultMaterial.shader.IsValid()) // this checks if the shader has been set (probably want a nicer way to do this)
    {
      _defaultMaterial = CreateDefaultMaterial(_shaderManager);
    }

    return _defaultMaterial;
  }

  Material& MaterialManager::GetMaterial(const Core::instanceId<Material>& material)
  {
  #if DEBUG
    if (auto iter = _materials.find(material); iter == _materials.end())
    {
      CORE_ERROR("MaterialManager", "Material not found! using default");
      return GetDefaultMaterial();
    }
  #endif

    return _materials[material];
  }
}// namespace Rendering
}// namespace Application