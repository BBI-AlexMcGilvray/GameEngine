#pragma once

#include "Dependencies\Includes\GLEW\glew.h"

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/ListDefs.h"

#include "Data/Rendering/Headers/MeshData.h"

using namespace Core;

namespace Application
{
	namespace Rendering
	{
		// holds the information about the mesh of a 3D object
		struct MeshBase : Data::Rendering::MeshData
		{
			GLuint Vao;
			List<GLuint> Vbos;

			MeshBase();
			MeshBase(String fileName);
		};
	}
}