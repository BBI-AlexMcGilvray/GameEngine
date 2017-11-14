#pragma once

#include "ApplicationManagement/Geometric/Headers/Node.h"

namespace Application
{
	namespace Geometric
	{
		// anything needed for camera. should create specifications for perspective and orthographic
		struct Camera : Node // inherits from node to have a transform, and to be able to be listed in the children of a scene (if needed?)
		{

		};
	}
}