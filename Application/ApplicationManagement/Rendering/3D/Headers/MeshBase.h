#pragma once

#include "Dependencies\Includes\GLEW\glew.h"

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/ListDefs.h"

using namespace Core;

namespace Application
{
	namespace Rendering
	{
		// holds the information about the mesh of a 3D object
		struct MeshBase
		{
			GLuint Vao;
			List<GLuint> Vbos;
			GLuint Texture;
			uint VertexCount = 0;

			MeshBase() = default;
		};
	}
}