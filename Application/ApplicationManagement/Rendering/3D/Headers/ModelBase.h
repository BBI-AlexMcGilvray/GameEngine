#pragma once

#include "ApplicationManagement/Rendering/2D/Headers/Material.h"
#include "ApplicationManagement/Rendering/3D/Headers/MeshBase.h"

namespace Application
{
	namespace Rendering
	{
		// holds the mesh, texture(s), and shader that a model uses
		struct ModelBase
		{
			Material material;
			MeshBase mesh;

			ModelBase(String folderName);
		};
	}
}