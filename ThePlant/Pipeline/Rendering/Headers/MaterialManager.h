#pragma once

#include <unordered_map>

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"
#include "Core/IdTypes/InstanceId.h"
#include "Core/Math/Headers/Color.h"
#include "Core/Math/Headers/Matrix4x4.h"

#include "Pipeline/Rendering/Material_NEW.h"

namespace Application {
namespace Rendering {
  struct RenderManager;

  // holds all render objects, handles updating them and passing them in to be rendered
  struct MaterialManager
  {
    MaterialManager(Core::Ptr<RenderManager> manager);

    void Initialize();
    void Start();

    void Update(Core::Second dt);

    void End();
    void CleanUp();

    template <typename ...ARGS>
    Core::instanceId<Material_NEW> AddMaterial(ARGS&& ...args)
    {
      return AddMaterial(CreateMaterial(std::forward<ARGS>(args)...));
    }

    Core::instanceId<Material_NEW> AddMaterial(const Material_NEW& material);
    Core::instanceId<Material_NEW> AddMaterial(Material_NEW&& material);
    void RemoveMaterial(const Core::instanceId<Material_NEW>& renderObject);

  private:
    // ideally we find a way to make this not a raw pointer, but it should be fine for now since this object
    // will only exist within a render manager, so lifetime is not a concern
    // ~ Could just be an element of this class and not a pointer at all?
    // ~ reference instead since it must exist?
    Core::Ptr<RenderManager> _manager;

    std::unordered_map<Core::instanceId<Material_NEW>, Material_NEW, Core::instanceIdHasher<Material_NEW>> _materials;
  };
}// namespace Rendering
}// namespace Application