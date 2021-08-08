#include "Pipeline/GameSystem/Headers/GameObjectManager.h"

#include "Pipeline/GameSystem/Headers/GameObjectBase.h"

namespace Application {
namespace GameSystem {
  void GameObjectManager::Initialize()
  {
  }

  void GameObjectManager::Update(Second dt)
  {
    for (auto &gameObject : GameObjects) {
      gameObject->Update(dt);
    }
  }

  void GameObjectManager::CleanUp()
  {
  }

  void GameObjectManager::AddGameObject(SharedPtr<GameObjectBase> gameObject)
  {
    Push(GameObjects, move(gameObject));
  }

  void GameObjectManager::RemoveGameObject(SharedPtr<GameObjectBase> gameObject)
  {
    Remove(GameObjects, move(gameObject));
  }
}// namespace GameSystem
}// namespace Application