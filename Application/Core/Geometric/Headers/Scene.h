#pragma once

#include "Core/Geometric/Headers/Node.h"

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/ListDefs.h"

namespace Core
{
	namespace Geometric
	{
		// a parent scene. holds a list of nodes (that represent that scene's content - all other content types should inherit from Node)
		struct Scene
		{
		protected:
			List<SharedPtr<Node>> Children;
		};
	}
}