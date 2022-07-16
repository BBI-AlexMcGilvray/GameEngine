#pragma once

#include <string>
#include <vector>

#include "Core/Headers/PtrDefs.h"

#include "Core/IO/Headers/File.h"

#include "Factory/Headers/Config.h"

struct aiScene;
struct aiMesh;
struct aiNode;
struct aiBone;

namespace Data
{
	namespace DataExport
	{
		struct ExportNode;

        // copy the texture to the right directory
        // do we need to store texture info like size/alpha?
		// void CreateFileForTexture(Config& config, Core::Ptr<Core::IO::File> directAssets, Core::Ptr<const aiScene> scene, Core::uint meshIndex, std::string name);
	}
}
