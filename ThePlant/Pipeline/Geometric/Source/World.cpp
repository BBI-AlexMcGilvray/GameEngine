#include "Pipeline/Geometric/Headers/World.h"

#include "Pipeline/Headers/ApplicationManager.h"

#if _DEBUG
#include "Pipeline/Geometric/Headers/ContentBase.h"
#include "Pipeline/Geometric/Headers/HierarchyComponent.h"
#endif

namespace Application {
namespace Geometric {
  World::World(Ptr<State> parentState)
    : Scene(parentState)
  {
  }

  void World::Initialize()
  {
    // does this need to deserialize components in data and create them?
    // probably, once worlds are data-driven
  }

  void World::Start()
  {
    ContainerBase::Start();

    for (auto &child : Children) {
      child->Start();
    }

#if _DEBUG
    // debug
    // Ptr<ContentBase> debugContent = AddContent<ContentBase>();

    // ComponentPtr<Hierarchy> hierarchyComponent = debugContent->GetComponent<Hierarchy>();
    // ComponentPtr<Rendering::Render> renderComponent = debugContent->AddComponent<Rendering::Render>(ApplicationManager::AppRenderManager().GetObjectManagerForState(ParentState));

    // renderComponent->SetRenderObject<Rendering::SphereRenderObject>(&(hierarchyComponent->GetHeirarchyNode()->Transformation), BLACK, 0.5f);
#endif
  }
}// namespace Geometric
}// namespace Application