#pragma once

#include "Core/Geometric/Headers/Node.h"

namespace Core
{
	namespace Geometric
	{
		// anything needed for camera. should create specifications for perspective and orthographic
		struct Camera : Node // inherits from node to have a transform, and to be able to be listed in the children of a scene (if needed?)
		{

		};
	}
}