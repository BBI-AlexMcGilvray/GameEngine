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
    GameObjects.push_back(move(gameObject));
  }

  void GameObjectManager::RemoveGameObject(SharedPtr<GameObjectBase> gameObject)
  {
    auto objectIter = std::find(GameObjects.begin(), GameObjects.end(), gameObject);
    if (objectIter != GameObjects.end())
    {
      GameObjects.erase(objectIter);
    }
  }
}// namespace GameSystem
}// namespace Application