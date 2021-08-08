#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/IO/Headers/File.h"

struct aiScene;
struct aiMesh;
struct aiMaterial;

namespace Data
{
	namespace DataExport
	{
		void CreateFileForMesh(Core::Ptr<Core::IO::File> directAssets, const aiMesh* mesh, Core::String name);
	}
}
