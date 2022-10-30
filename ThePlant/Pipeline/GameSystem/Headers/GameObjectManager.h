#pragma once

#include <vector>

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"
#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

using namespace Core;

namespace Application {
namespace GameSystem {
  struct GameObjectBase;

  struct GameObjectManager
  {
    virtual ~GameObjectManager();

    virtual void Initialize();
    virtual void Update(Second dt);
    virtual void CleanUp();

    template<typename T, typename... Ts>
    SharedPtr<T> AddGameObject(Ts &&...args)
    {
      SCOPED_MEMORY_CATEGORY("GameObject_OO");
      T newGameObject = MakeShared<T>(Forward<Ts>(args)...);

      AddGameObject(newGameObject);

      return newGameObject;
    }

    virtual void AddGameObject(SharedPtr<GameObjectBase> gameObject);
    virtual void RemoveGameObject(SharedPtr<GameObjectBase> gameObject);

  private:
    std::vector<SharedPtr<GameObjectBase>> GameObjects;
  };
}// namespace GameSystem
}// namespace Application