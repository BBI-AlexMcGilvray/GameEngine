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

		}

		GameObjectBase::~GameObjectBase()
		{

		}

		void GameObjectBase::Update(Second dt)
		{

		}
	}
}
