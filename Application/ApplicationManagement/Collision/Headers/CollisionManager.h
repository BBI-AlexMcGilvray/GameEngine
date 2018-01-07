#pragma once

#include "ColliderBase.h"
#include "CollisionBase.h"

#include "Core/Headers/ListDefs.h"

namespace Application
{
	namespace GameSystem
	{
		namespace Collision
		{
			struct CollisionManager
			{
				CollisionManager();

				virtual void Update(Second dt);

			private:
				List<ColliderBase> Colliders;
			};
		}
	}
}