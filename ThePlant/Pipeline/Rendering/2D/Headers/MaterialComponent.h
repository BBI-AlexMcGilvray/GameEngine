#pragma once

#include "Pipeline/Headers/Component.h"

#include "Pipeline/Rendering/2D/Headers/Material.h"

namespace Application {
namespace Rendering {
  struct MaterialManager;

  // a struct to hold all render objects of an entity
  struct MaterialComponent : Component<MaterialComponent>
  {
    static Core::Hash ClassHash()
    {
      return Core::HashValue("MaterialComponent");
    }

    MaterialComponent(Core::Ptr<EntityBase> entity, Core::Ptr<MaterialManager> materialManager);

    template<typename T, typename... Ts>
    Core::Ptr<T> SetMaterial(Ts &&...args)
    {
      return static_cast<Ptr<T>>(SetMaterial(MakeUnique<T>(Forward<Ts>(args)...)));
    }

    const Core::Ptr<Material> GetMaterial() const;
    Core::Ptr<Material> SetMaterial(Core::UniquePtr<Material> material);

    void RemoveMaterial();

  private:
    Core::Ptr<MaterialManager> _materialManager;
    Core::Ptr<Material> _material;
  };
}// namespace Rendering
}// namespace Application