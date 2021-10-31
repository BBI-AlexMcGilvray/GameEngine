#pragma once

#include "Pipeline/ECS/ObjectOriented/Headers/Component.h"

#include "Pipeline/Rendering/Headers/RenderObjectManager.h"

namespace Application {
namespace Rendering {
  struct RenderObjectManager;
  struct RenderObjectBase;

  // a struct to hold all render objects of an entity
  struct Render : Component<Render>
  {
    static Core::Hash ClassHash()
    {
      return Core::HashValue("Render");
    }

    Render(EntityBase& entity, Core::Ptr<RenderObjectManager> renderManager);

    template<typename T, typename... Ts>
    Core::Ptr<T> SetRenderObject(Ts &&...args)
    {
      // have this automatically get a transform component and add it?
      return static_cast<Ptr<T>>(SetRenderObject(RObjectManager->AddRenderObject<T>(Forward<Ts>(args)...)));
    }

    template<typename T>
    const Core::Ptr<T> GetRenderObject() const
    {
      return static_cast<Ptr<T>>(GetRenderObject());
    }

    const Core::Ptr<RenderObjectBase> GetRenderObject() const;

    Core::Ptr<RenderObjectBase> SetRenderObject(Core::UniquePtr<RenderObjectBase> renderObject);

    Core::Ptr<RenderObjectBase> SetRenderObject(Core::Ptr<RenderObjectBase> renderObject);

    void RemoveRenderObject();

  private:
    Core::Ptr<RenderObjectManager> RObjectManager;
    Core::Ptr<RenderObjectBase> RenderObject;
  };
}// namespace Rendering
}// namespace Application