#pragma once

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/ListDefs.h"

#include "Data/Headers/AssetData.h"
#include "Data/Rendering/Headers/SimpleMeshData.h"

#include "ApplicationManagement/Rendering/OpenGL/Headers/GLArrayBuffer.h"
#include "ApplicationManagement/Rendering/OpenGL/Headers/GLBuffer.h"

using namespace Core;

namespace Application
{
	namespace Rendering
	{
		// holds the information about the mesh of a 3D object
		struct SimpleMeshBase
		{
			Data::AssetData<Data::Rendering::SimpleMeshData> Data;
			GLArrayBuffer Vao;
			List<GLBuffer> Vbos;

			SimpleMeshBase(Data::AssetName<Data::Rendering::SimpleMeshData> asset);

			~SimpleMeshBase();

			virtual void Initialize();

			virtual void Prepare() const;
			virtual void CleanUp() const;
		};
	}
}