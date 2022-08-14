#pragma once

#include <unordered_map>

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"
#include "Core/IdTypes/InstanceId.h"
#include "Core/Math/Headers/Color.h"
#include "Core/Math/Headers/Matrix4x4.h"

#include "Pipeline/Rendering/Material.h"

namespace Application {
namespace Rendering {
  struct RenderManager;

  // NOTE: we probably want something like this for all meshes, skeletons, anything that is made up of large reusable data

  // should hold all materials for re-use
  struct MaterialManager
  {
    MaterialManager(Core::Ptr<RenderManager> manager);

    void Initialize();
    void Start();

    void Update(Core::Second dt);

    void End();
    void CleanUp();

    template <typename ...ARGS>
    Core::instanceId<Material> AddMaterial(ARGS&& ...args)
    {
      return AddMaterial(CreateMaterial(std::forward<ARGS>(args)...));
    }

    Core::instanceId<Material> AddMaterial(const Material& material);
    Core::instanceId<Material> AddMaterial(Material&& material);
    void RemoveMaterial(const Core::instanceId<Material>& renderObject);

  private:
    // ideally we find a way to make this not a raw pointer, but it should be fine for now since this object
    // will only exist within a render manager, so lifetime is not a concern
    // ~ Could just be an element of this class and not a pointer at all?
    // ~ reference instead since it must exist?
    Core::Ptr<RenderManager> _manager;

    std::unordered_map<Core::instanceId<Material>, Material, Core::instanceIdHasher<Material>> _materials;
  };
}// namespace Rendering
}// namespace Application