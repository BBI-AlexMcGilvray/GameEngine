#include "ApplicationManagement/Rendering/Headers/RenderObjectManager.h"

using namespace Core;

namespace Application {
namespace Rendering {
  RenderObjectManager::RenderObjectManager(Ptr<RenderManager> manager)
    : Manager(manager)
  {
  }

  void RenderObjectManager::Initialize()
  {
  }

  void RenderObjectManager::Start()
  {
  }

  void RenderObjectManager::Update(Second dt)
  {
    for (auto &renderObject : RenderObjects) {
      renderObject->Update(dt);
    }
  }

  void RenderObjectManager::Render(const Float4x4 &mvp, const Color &color)
  {
    // as noted in AddRenderObject, we will need to update this to having multiple lists and render them accordingly
    for (auto &renderObject : RenderObjects) {
      renderObject->Render(Manager, mvp, color);
    }
  }

  void RenderObjectManager::End()
  {
  }

  void RenderObjectManager::CleanUp()
  {
  }

  Ptr<RenderObjectBase> RenderObjectManager::AddRenderObject(UniquePtr<RenderObjectBase> renderObject)
  {
    // we will need some handling here for render objects to have types (animated, stagnant, alpha, solid) to be able to put them into different lists
    // for efficiency and general handling (ex: only update animated, alpha has to be rendered last IN Z ORDER to ensure correct rendering)

    Push(RenderObjects, move(renderObject));

    return RenderObjects[RenderObjects.size() - 1].get();
  }

  void RenderObjectManager::RemoveRenderObject(Ptr<RenderObjectBase> renderObject)
  {
    for (Core::size i = 0; i < RenderObjects.size(); i++) {
      if (RenderObjects[i].get() == renderObject) {
        RemoveIndex(RenderObjects, i);
      }
    }
  }
}// namespace Rendering
}// namespace Application