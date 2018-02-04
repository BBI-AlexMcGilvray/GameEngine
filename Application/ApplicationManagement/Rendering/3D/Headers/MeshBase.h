#pragma once

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/ListDefs.h"

#include "Data/Rendering/Headers/MeshData.h"

#include "ApplicationManagement/Rendering/OpenGL/Headers/GLArrayBuffer.h"
#include "ApplicationManagement/Rendering/OpenGL/Headers/GLBuffer.h"

using namespace Core;

namespace Application
{
	namespace Rendering
	{
		// holds the information about the mesh of a 3D object
		struct MeshBase : Data::Rendering::MeshData
		{
			GLArrayBuffer Vao;
			List<GLBuffer> Vbos;

			MeshBase();
			MeshBase(String fileName);

			virtual void Initialize();

			virtual void Prepare() const;
			virtual void Cleanup() const;
		};
	}
}