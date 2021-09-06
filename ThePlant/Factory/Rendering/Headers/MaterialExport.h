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
		void CreateFileForMaterial(Config& config, Core::Ptr<Core::IO::File> directAssets, const aiMaterial* material, Core::String name);
	}
}
