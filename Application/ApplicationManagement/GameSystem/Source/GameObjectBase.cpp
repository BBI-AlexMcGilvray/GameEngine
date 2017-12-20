#include "ApplicationManagement/GameSystem/Headers/GameObjectBase.h"

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
