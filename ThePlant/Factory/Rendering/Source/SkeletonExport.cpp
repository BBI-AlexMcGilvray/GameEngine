#include "Factory/Rendering/Headers/SkeletonExport.h"
#include "Factory/Rendering/Headers/Utils.h"
#include "Factory/Rendering/Headers/AssimpExtensions.h"

#include "Core/Headers/Hash.h"

#include "Core/Logging/Logger.h"

#include "Core/IO/Headers/File.h"
#include "Core/IO/Headers/Folder.h"
#include "Core/IO/Headers/IOUtils.h"

#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/Quaternion.h"

#include "Core/Serialization/Formats/JSON/JSON.h"
#include "Core/Serialization/Serialization.h"

#include "Data/Headers/SerializationUtils.h"
#include "Data/Rendering/Headers/SkeletonData.h"

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
		namespace
		{
			const std::string SKELETON_EXPORT = "Skeleton Export";
		}

		Data::Rendering::SkeletonBoneData CreateSkeletonBoneData(Core::Ptr<ExportNode> skeletonNode)
		{
			Data::Rendering::SkeletonBoneData skeletonBoneData;

			aiMatrix4x4 nodeMatrix = skeletonNode->mTransformation;

			aiVector3D scaling;
			aiQuaterniont<float> rotation;
			aiVector3D position;
			nodeMatrix.Decompose(scaling, rotation, position);

			skeletonBoneData.name = std::string(skeletonNode->mName.C_Str());
			skeletonBoneData.position = Core::Math::Float3(position.x, position.y, position.z);
			skeletonBoneData.rotation = Core::Math::FQuaternion(rotation.x, rotation.y, rotation.z, rotation.w);
			skeletonBoneData.scale = Core::Math::Float3(scaling.x, scaling.y, scaling.z);
			skeletonBoneData.children = skeletonNode->mNumChildren;

			return skeletonBoneData;
		}

		void FillInSkeletonData(std::vector<Data::Rendering::SkeletonBoneData>& skeletonData, Core::Ptr<ExportNode> skeletonNode)
		{
			skeletonData.push_back(CreateSkeletonBoneData(skeletonNode));

			for (uint i = 0; i < skeletonNode->mNumChildren; i++)
			{
				FillInSkeletonData(skeletonData, static_cast<Core::Ptr<ExportNode>>(skeletonNode->mChildren[i]));
			}
		}

		Core::Serialization::Format::JSON SerializeSkeleton(Ptr<const aiScene> scene, uint meshIndex, String name)
		{
			Data::Rendering::SkeletonData skeletonData;
			
			Core::Ptr<const aiNode> rootNode = scene->mRootNode;
			Core::Ptr<const aiMesh> mesh = scene->mMeshes[meshIndex];
			Core::UniquePtr<ExportNode> exportSkeleton = AllNodesForMesh(rootNode, mesh, meshIndex);
			FillInSkeletonData(skeletonData.bones, exportSkeleton.get());

			for (uint animationIndex = 0; animationIndex < scene->mNumAnimations; animationIndex++)
			{
				skeletonData.animations.push_back(HashValue(std::string(scene->mAnimations[animationIndex]->mName.C_Str())));
			}

			return Core::Serialize<Core::Serialization::Format::JSON>(skeletonData);
		}

		void CreateFileForSkeleton(Config& config, Core::Ptr<Core::IO::File> directAssets, Ptr<const aiScene> scene, uint meshIndex, String name)
		{
			Core::Ptr<const aiNode> rootNode = scene->mRootNode;
			Core::Ptr<const aiMesh> mesh = scene->mMeshes[meshIndex];

			if (!mesh->HasBones())
			{
				CORE_LOG(SKELETON_EXPORT, "Given skeleton <<" + name + ">> does not exist");
				return;
			}

			// Core::UniquePtr<ExportNode> exportSkeleton = AllNodesForMesh(rootNode, mesh, meshIndex);

			// store values in file
			Core::IO::FilePath skeletonFilePath = Core::IO::FilePath{ GetCWD() + config.getValue("exportPath") + config.getValue("skeletonsPath"), to_string(HashValue(name)) + ".skl" };
			Core::IO::File skeletonFile = File(skeletonFilePath, ios::out);
			skeletonFile.Open();

			// if (!skeletonFile.FileStream.is_open())
			// {
			// 	CORE_LOG(SKELETON_EXPORT, "Could not open file <<" + skeletonFilePath.GetFullPath() + ">>");
			// 	return;
			// }

			// skeletonFile.Write("animations", scene->mNumAnimations);
			// skeletonFile.CreateNewLine();
			// for (uint animationIndex = 0; animationIndex < scene->mNumAnimations; animationIndex++)
			// {
			// 	skeletonFile.Write(to_string(HashValue(String(scene->mAnimations[animationIndex]->mName.C_Str()))));
			// 	skeletonFile.CreateNewLine();
			// }

			// AddSkeletonToFile(&skeletonFile, move(exportSkeleton), mesh);

			Core::Serialization::Format::JSON skeletonAsJSON = SerializeSkeleton(scene, meshIndex, name);
			skeletonFile.Write(skeletonAsJSON.ToString(Core::Serialization::Format::Style::Readable));

			skeletonFile.Close();
		}

		// void AddSkeletonToFile(Core::Ptr<Core::IO::File> skeletonFile, Core::UniquePtr<ExportNode> exportSkeleton, Core::Ptr<const aiMesh> mesh)
		// {
		// 	AddBoneToFile(skeletonFile, exportSkeleton.get(), mesh);
		// }

		// void AddBoneToFile(Core::Ptr<Core::IO::File> skeletonFile, Core::Ptr<const ExportNode> exportSkeleton, Core::Ptr<const aiMesh> mesh)
		// {
		// 	Core::Ptr<const aiBone> skeletonBone = GetBoneForNode(mesh, exportSkeleton);

		// 	if (skeletonBone != nullptr)
		// 	{
		// 		aiMatrix4x4 inverseBindMatrix = skeletonBone->mOffsetMatrix;
		// 		aiMatrix4x4 bindMatrix = inverseBindMatrix.Inverse();

		// 		aiVector3D scaling;
		// 		aiQuaterniont<float> rotation;
		// 		aiVector3D position;

		// 		bindMatrix.Decompose(scaling, rotation, position);

		// 		skeletonFile->Write(String(skeletonBone->mName.C_Str()), exportSkeleton->mNumChildren);
		// 		skeletonFile->Write(", scaling", scaling.x, scaling.y, scaling.z);
		// 		skeletonFile->Write(", rotation", rotation.x, rotation.y, rotation.z, rotation.w);
		// 		skeletonFile->Write(", position", position.x, position.y, position.z);

		// 		skeletonFile->CreateNewLine();
		// 	}
		// 	else
		// 	{
		// 		aiMatrix4x4 nodeMatrix = exportSkeleton->mTransformation;

		// 		aiVector3D scaling;
		// 		aiQuaterniont<float> rotation;
		// 		aiVector3D position;

		// 		nodeMatrix.Decompose(scaling, rotation, position);

		// 		skeletonFile->Write(String(exportSkeleton->mName.C_Str()), exportSkeleton->mNumChildren);
		// 		skeletonFile->Write(", scaling", scaling.x, scaling.y, scaling.z);
		// 		skeletonFile->Write(", rotation", rotation.x, rotation.y, rotation.z, rotation.w);
		// 		skeletonFile->Write(", position", position.x, position.y, position.z);

		// 		skeletonFile->CreateNewLine();
		// 	}

		// 	for (int i = 0; i < exportSkeleton->mNumChildren; i++)
		// 	{
		// 		AddBoneToFile(skeletonFile, static_cast<Core::Ptr<const ExportNode>>(exportSkeleton->mChildren[i]), mesh);
		// 	}
		// }

		// // not sure why this is needed, it lets us use the bone instead of a node if available, but why do we need to?
		// Core::Ptr<const aiBone> GetBoneForNode(Core::Ptr<const aiMesh> mesh, Core::Ptr<const ExportNode> node)
		// {
		// 	for (int i = 0; i < mesh->mNumBones; i++)
		// 	{
		// 		if (mesh->mBones[i]->mName == node->mName)
		// 		{
		// 			return mesh->mBones[i];
		// 		}
		// 	}

		// 	return nullptr;
		// }
	}
}
