#pragma once

#include "Factory/Rendering/Headers/SkeletonExport.h"
#include "Factory/Rendering/Headers/Utils.h"
#include "Factory/Rendering/Headers/AssimpExtensions.h"

#include "Core/Headers/Hash.h"

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
		void CreateFileForSkeleton(Core::Ptr<Core::IO::File> directAssets, Ptr<const aiScene> scene, uint meshIndex, String name)
		{
			Core::Ptr<const aiNode> rootNode = scene->mRootNode;
			Core::Ptr<const aiMesh> mesh = scene->mMeshes[meshIndex];

			if (!mesh->HasBones())
			{
				LOG("Given skeleton <<" + name + ">> does not exist");
				return;
			}

			Core::Ptr<const aiNode> rootNodeForMesh = FindRootNodeForMesh(rootNode, meshIndex);
			Core::UniquePtr<ExportNode> exportSkeleton = AllNodesForMesh(rootNode, mesh, meshIndex);

			// store values in file
			Core::IO::FilePath skeletonFilePath = Core::IO::FilePath{ GetCWD() + "/Resources/ExportedAssets/Skeletons/", ToString(HashValue(name)) + ".skl" };
			Core::IO::File skeletonFile = File(skeletonFilePath, ios::out);
			skeletonFile.Open();

			if (!skeletonFile.FileStream.is_open())
			{
				LOG("Could not open file <<" + skeletonFilePath.GetFullPath() + ">>");
				return;
			}

			skeletonFile.Write("animations", scene->mNumAnimations);
			skeletonFile.CreateNewLine();
			for (uint animationIndex = 0; animationIndex < scene->mNumAnimations; animationIndex++)
			{
				skeletonFile.Write(ToString(HashValue(String(scene->mAnimations[animationIndex]->mName.C_Str())).H));
				skeletonFile.CreateNewLine();
			}

			AddSkeletonToFile(&skeletonFile, move(exportSkeleton), mesh);

			skeletonFile.Close();
		}

		void AddSkeletonToFile(Core::Ptr<Core::IO::File> skeletonFile, Core::UniquePtr<ExportNode> exportSkeleton, Core::Ptr<const aiMesh> mesh)
		{
			AddBoneToFile(skeletonFile, exportSkeleton.get(), mesh);
		}

		void AddBoneToFile(Core::Ptr<Core::IO::File> skeletonFile, Core::Ptr<const ExportNode> exportSkeleton, Core::Ptr<const aiMesh> mesh)
		{
			Core::Ptr<const aiBone> skeletonBone = GetBoneForNode(mesh, exportSkeleton);

			if (skeletonBone != nullptr)
			{
				aiMatrix4x4 inverseBindMatrix = skeletonBone->mOffsetMatrix;
				aiMatrix4x4 bindMatrix = inverseBindMatrix.Inverse();

				aiVector3D scaling;
				aiQuaterniont<float> rotation;
				aiVector3D position;

				bindMatrix.Decompose(scaling, rotation, position);

				skeletonFile->Write(String(skeletonBone->mName.C_Str()), exportSkeleton->mNumChildren);
				skeletonFile->Write(", scaling", scaling.x, scaling.y, scaling.z);
				skeletonFile->Write(", rotation", rotation.x, rotation.y, rotation.z, rotation.w);
				skeletonFile->Write(", position", position.x, position.y, position.z);

				skeletonFile->CreateNewLine();
			}
			else
			{
				aiMatrix4x4 nodeMatrix = exportSkeleton->mTransformation;

				aiVector3D scaling;
				aiQuaterniont<float> rotation;
				aiVector3D position;

				nodeMatrix.Decompose(scaling, rotation, position);

				skeletonFile->Write(String(exportSkeleton->mName.C_Str()), exportSkeleton->mNumChildren);
				skeletonFile->Write(", scaling", scaling.x, scaling.y, scaling.z);
				skeletonFile->Write(", rotation", rotation.x, rotation.y, rotation.z, rotation.w);
				skeletonFile->Write(", position", position.x, position.y, position.z);

				skeletonFile->CreateNewLine();
			}

			for (int i = 0; i < exportSkeleton->mNumChildren; i++)
			{
				AddBoneToFile(skeletonFile, static_cast<Core::Ptr<const ExportNode>>(exportSkeleton->mChildren[i]), mesh);
			}
		}

		Core::Ptr<const aiBone> GetBoneForNode(Core::Ptr<const aiMesh> mesh, Core::Ptr<const ExportNode> node)
		{
			for (int i = 0; i < mesh->mNumBones; i++)
			{
				if (mesh->mBones[i]->mName == node->mName)
				{
					return mesh->mBones[i];
				}
			}

			return nullptr;
		}
	}
}
