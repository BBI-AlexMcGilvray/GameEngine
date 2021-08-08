#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/ListDefs.h"

#include "Core/IO/Headers/File.h"

#include "Factory/Rendering/Headers/AssimpExtensions.h"

struct aiScene;
struct aiMesh;
struct aiNode;

namespace Data
{
	namespace DataExport
	{
		Core::Ptr<const aiNode> FindRootNodeForMesh(Core::Ptr<const aiNode> rootNode, Core::uint meshIndex);
		Core::Ptr<const aiNode> FindNodeForMesh(Core::Ptr<const aiNode> rootNode, Core::uint meshIndex);
		Core::Ptr<const aiNode> FindNodeWithName(Core::Ptr<const aiNode> rootNode, Core::String name);

		Core::UniquePtr<ExportNode> AllNodesForMesh(Core::Ptr<const aiNode> rootNode, Core::Ptr<const aiMesh> mesh, Core::uint meshIndex);

		Core::UniquePtr<ExportNode> CreateExportSkeletonForMesh(Core::Ptr<const aiNode> rootNode, Core::uint meshIndex);
	}
}
