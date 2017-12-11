#pragma once

#include "Core/Math/Headers/Vector3.h"

using namespace Core::Math;

namespace Application
{
	namespace Rendering
	{
		struct VertexBase
		{
			Float3 Position; // standard vertex attribute
			Float3 Normal; // nvertex normal

			VertexBase(const Float3& pos, const Float3& normal)
			{
				Position = pos;
				Normal = normal;
			}
		};
	}
}