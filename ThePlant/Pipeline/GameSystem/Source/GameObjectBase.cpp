#include "Pipeline/GameSystem/Headers/GameObjectBase.h"

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"

namespace Application {
namespace GameSystem {
  GameObjectBase::GameObjectBase()
  {
    SCOPED_MEMORY_CATEGORY("Logger");
    ObjectTransform = MakeShared<Transform>();
  }

  GameObjectBase::GameObjectBase(SharedPtr<Transform> transform)
    : ObjectTransform(move(transform))
  {
  }

  GameObjectBase::~GameObjectBase()
  {
  }

  void GameObjectBase::Update(Second dt)
  {
  }
}// namespace GameSystem
}// namespace Application
