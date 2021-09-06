#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/IO/Headers/File.h"

#include "Factory/Headers/Config.h"

struct aiScene;
struct aiMesh;
struct aiMaterial;

namespace Data
{
	namespace DataExport
	{
		void CreateFileForMesh(Config& config, Core::Ptr<Core::IO::File> directAssets, const aiMesh* mesh, Core::String name);
	}
}
