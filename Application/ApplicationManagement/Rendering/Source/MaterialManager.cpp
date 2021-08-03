#include "ApplicationManagement/Rendering/Headers/MaterialManager.h"

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
    for (auto &material : _materials) {
      material->Update(dt);
    }
  }

  // maybe not necessary
  void MaterialManager::Render(const Float4x4 &mvp, const Color &color)
  {
  }

  void MaterialManager::End()
  {
  }

  void MaterialManager::CleanUp()
  {
  }

  Ptr<Material> MaterialManager::AddMaterial(UniquePtr<Material> material)
  {
    // we will need some handling here for render objects to have types (animated, stagnant, alpha, solid) to be able to put them into different lists
    // for efficiency and general handling (ex: only update animated, alpha has to be rendered last IN Z ORDER to ensure correct rendering)

    Push(_materials, move(material));

    return _materials[_materials.size() - 1].get();
  }

  void MaterialManager::RemoveMaterial(Ptr<Material> material)
  {
    for (Core::size i = 0; i < _materials.size(); i++) {
      if (_materials[i].get() == material) {
        RemoveIndex(_materials, i);
      }
    }
  }
}// namespace Rendering
}// namespace Application