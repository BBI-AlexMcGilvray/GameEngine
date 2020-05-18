#pragma once

#include "ApplicationManagement/Geometric/Headers/Scene.h"

namespace Application
{
	namespace Geometric
	{
		// a world is a scene, but it also has a camera (and probably more stuff in the future)
		struct World : Scene
		{
			World(Core::Ptr<State> parentState);

			void Start() override;

			// debugging
			Core::Ptr<Node> holderNode;
			Core::Ptr<Node> neckBone;
			void Update(Second dt) override;
		};
	}
}