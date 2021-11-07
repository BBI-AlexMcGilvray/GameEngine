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
		void CreateFileForModel(Config& config, Core::Ptr<Core::IO::File> directAssets, Core::Ptr<const aiScene> scene, Core::uint meshIndex, std::string name);
	}
}
