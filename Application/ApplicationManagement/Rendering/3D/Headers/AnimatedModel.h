#pragma once

#include "ApplicationManagement/Rendering/3D/Headers/ModelBase.h"

namespace Application
{
	namespace Rendering
	{
		// holds positional information for each bone that the mesh is weighted against
		struct Bone
		{

		};

		// is a model,  but also has a list of timelines that can be called for animations
		// also holds a list of the relevant bones
		struct AnimatedModel : ModelBase
		{

		};
	}
}