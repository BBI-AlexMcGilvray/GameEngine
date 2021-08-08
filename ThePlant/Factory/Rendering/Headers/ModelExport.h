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
		void CreateFileForModel(Core::Ptr<Core::IO::File> directAssets, Core::Ptr<const aiScene> scene, Core::uint meshIndex, Core::String name);
	}
}
