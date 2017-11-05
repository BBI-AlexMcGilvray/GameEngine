#include "ApplicationManagement/GameSystem/Headers/GameObject.h"

namespace Application
{
	namespace GameSystem
	{
		GameObjectBase::GameObjectBase()
			: ObjectTransform(MakeShared<Transform>())
		{

		}
		GameObjectBase:: ~GameObjectBase()
		{

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
