#pragma once

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/ListDefs.h"

#include "Data/Headers/AssetData.h"
#include "Data/Rendering/Headers/AnimatedMeshData.h"

#include "ApplicationManagement/Rendering/OpenGL/Headers/GLArrayBuffer.h"
#include "ApplicationManagement/Rendering/OpenGL/Headers/GLBuffer.h"

using namespace Core;

namespace Application
{
	namespace Rendering
	{
		// holds the information about the mesh of a 3D object
		struct SkinnedMeshBase
		{
			Data::AssetData<Data::Rendering::AnimatedMeshData> Data;
			GLArrayBuffer Vao;
			List<GLBuffer> Vbos;

			SkinnedMeshBase(Data::AssetName<Data::Rendering::AnimatedMeshData> asset);

			virtual void Initialize();

			virtual void Prepare() const;
			virtual void CleanUp() const;
		};
	}
}