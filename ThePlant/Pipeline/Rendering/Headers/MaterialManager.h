#pragma once

#include "Pipeline/Rendering/2D/Headers/Material.h"

#include "Core/Headers/ListDefs.h"
#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

#include "Core/Math/Headers/Color.h"
#include "Core/Math/Headers/Matrix4x4.h"

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
    // maybe not necessary
    void Render(const Core::Math::Float4x4 &mvp, const Core::Math::Color &color);

    void End();
    void CleanUp();

    // This should return a RanderObjectPtr that holds a unique ptr to the render object and will remove the object from
    // the manager once deleted
    template<typename T, typename... Ts>
    Core::Ptr<T> AddMaterial(Ts &&...args)
    {
      Core::UniquePtr<Material> newMaterial = Core::MakeUnique<T>(_manager, Forward<Ts>(args)...);

      return static_cast<Ptr<T>>(AddRenderObject(move(newRenderObject)));
    }

    virtual Core::Ptr<Material> AddMaterial(Core::UniquePtr<Material> material);
    virtual void RemoveMaterial(Core::Ptr<Material> renderObject);

  private:
    // ideally we find a way to make this not a raw pointer, but it should be fine for now since this object
    // will only exist within a render manager, so lifetime is not a concern
    // ~ Could just be an element of this class and not a pointer at all?
    // ~ reference instead since it must exist?
    Core::Ptr<RenderManager> _manager;

    // Should this not be ptrs at all to have contiguous memory?
    // ~ that would mean they would need to live here, and not on a component
    // ~ so components point to element held by array within the system instead of the other way around
    Core::List<Core::UniquePtr<Material>> _materials;
  };
}// namespace Rendering
}// namespace Application