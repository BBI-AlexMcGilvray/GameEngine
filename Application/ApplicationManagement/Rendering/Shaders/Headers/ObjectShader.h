#pragma once

namespace Application
{
	namespace Rendering
	{
		// holds onto name (for reflection) and a pixel/vertex shader combination
		struct ObjectShader
		{
			// perhaps I can use the R() function to build up the shaders out or parts. each actual shader would have a reference to a static fragment/vertex shader and would load in the various parts to create the full code out of each bit and piece
		};
	}
}