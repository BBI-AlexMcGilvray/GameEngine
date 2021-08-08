#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/ListDefs.h"

#include "Core/IO/Headers/File.h"

#include "ASSIMP/matrix4x4.h"

struct aiScene;
struct aiMesh;
struct aiNode;
struct aiBone;

namespace Data
{
	namespace DataExport
	{
		struct ExportNode;

		void CreateFileForSkeleton(Core::Ptr<Core::IO::File> directAssets, Core::Ptr<const aiScene> scene, Core::uint meshIndex, Core::String name);

		void AddSkeletonToFile(Core::Ptr<Core::IO::File> skeletonFile, Core::UniquePtr<ExportNode> exportSkeleton, Core::Ptr<const aiMesh> mesh);
		void AddBoneToFile(Core::Ptr<Core::IO::File> skeletonFile, Core::Ptr<const ExportNode> exportSkeleton, Core::Ptr<const aiMesh> mesh);

		Core::Ptr<const aiBone> GetBoneForNode(Core::Ptr<const aiMesh> mesh, Core::Ptr<const ExportNode> node);
	}
}
