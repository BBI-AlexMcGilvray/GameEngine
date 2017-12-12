#pragma once

#include "Core/Math/Headers/Vector3.h"

using namespace Core::Math;

namespace Data
{
	namespace Rendering
	{
		struct VertexDataBase
		{
			Float3 Position; // standard vertex attribute
			Float3 Normal; // nvertex normal

			VertexDataBase()
			{}

			VertexDataBase(const Float3& pos, const Float3& normal)
			{
				Position = pos;
				Normal = normal;
			}
		};
	}
}