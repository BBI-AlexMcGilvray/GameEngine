#pragma once

#include <unordered_map>

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"
#include "Core/IdTypes/InstanceId.h"
#include "Core/Math/Headers/Color.h"
#include "Core/Math/Headers/Matrix4x4.h"

#include "Data/Headers/AssetManager.h"
#include "Data/Rendering/Headers/MaterialData.h"

#include "Pipeline/AssetHandling/AssetLoaderFactory.h"
#include "Pipeline/Rendering/Material.h"
#include "Pipeline/Rendering/Shaders/ShaderManager.h"

namespace Application {
namespace Rendering {
  struct RenderManager;

  // NOTE: we probably want something like this for all meshes, skeletons, anything that is made up of large reusable data

  // should hold all materials for re-use
  struct MaterialManager
  {
    MaterialManager(Data::AssetManager& assetManager, AssetLoaderFactory& assetLoaderFactory, ShaderManager& shaderManager);
    ~MaterialManager();

    void Initialize();
    void Start();

    void Update(Core::Second dt);

    void End();
    void CleanUp();

    // should we be using instanceIds? should we just use asset names?
    Core::instanceId<Material> AddMaterial(const Data::AssetName<Data::Rendering::MaterialData>& material);
    // NOTE: We shouldn't need to worry about this being thread safe if shaders are thread safe, as materials really just rely on shaders existing
    void RemoveMaterial(const Core::instanceId<Material>& renderObject);

    Material& GetDefaultMaterial();
    Material& GetMaterial(const Core::instanceId<Material>& material);

  private:
    Data::AssetManager& _assetManager;
    AssetLoaderFactory& _assetLoaderFactory;
    ShaderManager& _shaderManager;

    Material _defaultMaterial;
    std::unordered_map<Core::instanceId<Material>, Material, Core::instanceIdHasher<Material>> _materials;
  };
}// namespace Rendering
}// namespace Application