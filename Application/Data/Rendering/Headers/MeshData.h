#pragma once

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/ListDefs.h"

#include "VertexBaseData.h"

using namespace Core;

namespace Data
{
	namespace Rendering
	{
		// holds the information about the mesh of a 3D object
		struct MeshData
		{
			List<VertexDataBase> Vertices;
			uint VertexCount = 0;

			MeshData() = default;
			MeshData(String fileName);
		};
	}
}