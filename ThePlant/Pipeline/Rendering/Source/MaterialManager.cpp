#include "Pipeline/Rendering/Headers/MaterialManager.h"

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

  Core::instanceId<Material_NEW> MaterialManager::AddMaterial(const Material_NEW& material)
  {
    Core::instanceId<Material_NEW> newId = GetInstanceId<Material_NEW>();

    _materials.emplace(std::make_pair(newId, material));

    return newId;
  }

  Core::instanceId<Material_NEW> MaterialManager::AddMaterial(Material_NEW&& material)
  {
    Core::instanceId<Material_NEW> newId = GetInstanceId<Material_NEW>();

    _materials.emplace(std::make_pair(newId, std::move(material)));

    return newId;
  }

  void MaterialManager::RemoveMaterial(const Core::instanceId<Material_NEW>& materialId)
  {
    _materials.erase(materialId);
  }
}// namespace Rendering
}// namespace Application