#pragma once

#include "Core/Headers/ListDefs.h"
#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

using namespace Core;

namespace Application
{
	namespace GameSystem
	{
		struct GameObjectBase;

		struct GameObjectManager
		{
			virtual void Initialize();
			virtual void Update(Second dt);
			virtual void CleanUp();

			template <typename T, typename ...Ts>
			SharedPtr<T> AddGameObject(Ts ...args)
			{
				T newGameObject = MakeShared<T>(Forward<Ts>(args)...);

				AddGameObject(newGameObject);

				return newGameObject;
			}

			virtual void AddGameObject(SharedPtr<GameObjectBase> gameObject);
			virtual void RemoveGameObject(SharedPtr<GameObjectBase> gameObject);

		private:
			List<SharedPtr<GameObjectBase>> GameObjects;
		};
	}
}