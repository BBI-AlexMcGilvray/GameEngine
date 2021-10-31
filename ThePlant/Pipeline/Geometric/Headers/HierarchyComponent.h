#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/Hash.h"

#include "Pipeline/Geometric/Headers/Node.h"
#include "Pipeline/ECS/ObjectOriented/Headers/Component.h"

namespace Application {
namespace Geometric {
  // a recursive struct to hold elements in a scene
  struct Hierarchy : Component<Hierarchy>
  {
    static Core::Hash ClassHash()
    {
      return Core::HashValue("Hierarchy");
    }

    Hierarchy(EntityBase& entity);
    Hierarchy(EntityBase& entity, Core::Ptr<Node> hierarchyNode);

    void SetHierarchyNode(Core::Ptr<Node> hierarchyNode);
    Core::Ptr<Node> GetHeirarchyNode() const;

  private:
    Delegate<> OnNodeDeleted;

    Core::Ptr<Node> HierarchyNode = nullptr;
  };
}// namespace Geometric
}// namespace Application