#include "Pipeline/Rendering/Headers/MaterialManager.h"

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"

using namespace Core;

namespace Application {
namespace Rendering {
  MaterialManager::MaterialManager(Ptr<RenderManager> manager)
    : _manager(manager)
  {
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

  Core::instanceId<Material> MaterialManager::AddMaterial(const Material& material)
  {
    SCOPED_MEMORY_CATEGORY("Rendering");
    Core::instanceId<Material> newId = GetInstanceId<Material>();

    _materials.emplace(std::make_pair(newId, material));

    return newId;
  }

  Core::instanceId<Material> MaterialManager::AddMaterial(Material&& material)
  {
    SCOPED_MEMORY_CATEGORY("Rendering");
    Core::instanceId<Material> newId = GetInstanceId<Material>();

    _materials.emplace(std::make_pair(newId, std::move(material)));

    return newId;
  }

  void MaterialManager::RemoveMaterial(const Core::instanceId<Material>& materialId)
  {
    _materials.erase(materialId);
  }
}// namespace Rendering
}// namespace Application