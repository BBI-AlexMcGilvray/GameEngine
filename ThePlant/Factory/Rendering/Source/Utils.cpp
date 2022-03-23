#pragma once

#include "Factory/Rendering/Headers/Utils.h"

#include "Core/Headers/Hash.h"

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"
#include "Core/Debugging/Headers/Macros.h"

#include "Core/IO/Headers/File.h"
#include "Core/IO/Headers/Folder.h"
#include "Core/IO/Headers/IOUtils.h"

#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/Quaternion.h"

#include "ASSIMP/cimport.h"
#include "ASSIMP/scene.h"
#include "ASSIMP/postprocess.h"

using namespace std;
using namespace Core;
using namespace Core::IO;
using namespace Core::Math;

namespace Data
{
	namespace DataExport
	{
		Ptr<const aiNode> FindRootNodeForMesh(Ptr<const aiNode> rootNode, uint meshIndex)
		{
			Ptr<const aiNode> meshNode = FindNodeForMesh(rootNode, meshIndex);

			if (meshNode == nullptr)
			{
				return rootNode;
			}

			if (meshNode->mParent != nullptr)
			{
				return meshNode->mParent;
			}

			return meshNode;
		}

		Ptr<const aiNode> FindNodeForMesh(Ptr<const aiNode> rootNode, uint meshIndex)
		{
			for (uint i = 0; i < rootNode->mNumMeshes; i++)
			{
				if (rootNode->mMeshes[i] == meshIndex)
				{
					return rootNode;
				}
			}

			for (uint i = 0; i < rootNode->mNumChildren; i++)
			{
				Ptr<const aiNode> rootNodeForMesh = FindNodeForMesh(rootNode->mChildren[i], meshIndex);
				if (rootNodeForMesh != nullptr)
				{
					return rootNodeForMesh;
				}
			}

			return nullptr;
		}

		Ptr<const aiNode> FindNodeWithName(Ptr<const aiNode> rootNode, std::string name)
		{
			if (rootNode->mName == aiString(name))
			{
				return rootNode;
			}

			for (uint i = 0; i < rootNode->mNumChildren; i++)
			{
				Ptr<const aiNode> nodeWtihName = FindNodeWithName(rootNode->mChildren[i], name);
				if (nodeWtihName != nullptr)
				{
					return nodeWtihName;
				}
			}

			return nullptr;
		}

		Core::UniquePtr<ExportNode> AllNodesForMesh(Core::Ptr<const aiNode> rootNode, Core::Ptr<const aiMesh> mesh, Core::uint meshIndex)
		{
			Core::UniquePtr<ExportNode> meshSkeleton = CreateExportSkeletonForMesh(rootNode, meshIndex);

			for (Core::uint i = 0; i < mesh->mNumBones; i++)
			{
				meshSkeleton->IncludeNode(std::string(mesh->mBones[i]->mName.C_Str()));
			}

			meshSkeleton->CleanStructure();

			return move(meshSkeleton);
		}

		Core::UniquePtr<ExportNode> CreateExportSkeletonForMesh(Core::Ptr<const aiNode> rootNode, Core::uint meshIndex)
		{
			SCOPED_MEMORY_CATEGORY("DataExport");
			Core::Ptr<const aiNode> meshRoot = FindRootNodeForMesh(rootNode, meshIndex);

			Core::UniquePtr<ExportNode> exportSkeleton = Core::MakeUnique<ExportNode>(meshRoot);

			return exportSkeleton;
		}
	}
}
