#include "ApplicationManagement/GameSystem/Headers/GameObjectBase.h"

namespace Application
{
	namespace GameSystem
	{
		GameObjectBase::GameObjectBase()
			: GameObjectBase(MakeShared<Transform>())
		{}

		GameObjectBase::GameObjectBase(SharedPtr<Transform> transform)
			: ObjectTransform(move(transform))
		{
			SubscribeToGameManager();
		}

		GameObjectBase:: ~GameObjectBase()
		{
			UnsubscribeFromGameManager();
		}

		void GameObjectBase::Update(Second dt)
		{

		}

		void GameObjectBase::SubscribeToGameManager()
		{

		}

		void GameObjectBase::UnsubscribeFromGameManager()
		{

		}
	}
}
