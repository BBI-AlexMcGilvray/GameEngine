#pragma once

#include "Factory/Rendering/Headers/SkeletonAnimationExport.h"
#include "Factory/Rendering/Headers/Utils.h"
#include "Factory/Rendering/Headers/AssimpExtensions.h"

#include "Core/Headers/Hash.h"

#include "Core/Logging/Logger.h"

#include "Core/IO/Headers/File.h"
#include "Core/IO/Headers/Folder.h"
#include "Core/IO/Headers/IOUtils.h"

#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/Quaternion.h"

#include "ASSIMP/cimport.h"
#include "ASSIMP/scene.h"
#include "ASSIMP/postprocess.h"

using namespace Core;
using namespace Core::IO;
using namespace Core::Math;

namespace Data
{
	namespace DataExport
	{
		namespace
		{
			const std::string SKELETON_ANIMATION_EXPORT = "Skeleton Animation Export";
		}

		void CreateFileForSkeletonAnimation(Core::Ptr<Core::IO::File> directAssets, Core::Ptr<aiAnimation> animation, Ptr<const aiNode> rootNode, Ptr<const aiMesh> mesh, uint meshIndex, String name)
		{
			if (animation == nullptr)
			{
				CORE_LOG(SKELETON_ANIMATION_EXPORT, "Given skeleton <<" + name + ">> does not exist");
				return;
			}

			Ptr<const aiNode> rootNodeForMesh = FindRootNodeForMesh(rootNode, meshIndex);
			Core::UniquePtr<ExportNode> exportSkeleton = AllNodesForMesh(rootNode, mesh, meshIndex);

			// store values in file
			FilePath skeletonAnimationFilePath = FilePath{ GetCWD() + "/Resources/ExportedAssets/SkeletonAnimations/", ToString(HashValue(name + String(animation->mName.C_Str()))) + ".sanim" };
			File skeletonAnimationFile = File(skeletonAnimationFilePath, std::ios::out);
			skeletonAnimationFile.Open();

			if (!skeletonAnimationFile.FileStream.is_open())
			{
				CORE_LOG(SKELETON_ANIMATION_EXPORT, "Could not open file <<" + skeletonAnimationFile.GetFullPath() + ">>");
				return;
			}

			skeletonAnimationFile.Write(String(animation->mName.C_Str()), animation->mNumChannels, animation->mDuration / animation->mTicksPerSecond);

			for (uint i = 0; i < animation->mNumChannels; i++)
			{
				if (exportSkeleton->FindNode(animation->mChannels[i]->mNodeName.C_Str()) != nullptr)
				{
					AddChannelToFile(&skeletonAnimationFile, animation->mChannels[i], animation->mTicksPerSecond);
				}
			}

			skeletonAnimationFile.Close();
		}

		void AddChannelToFile(Core::Ptr<Core::IO::File> skeletonAnimationFile, Core::Ptr<const aiNodeAnim> channel, double ticksPerSecond)
		{
			skeletonAnimationFile->CreateNewLine();
			skeletonAnimationFile->Write(String(channel->mNodeName.C_Str()));

			skeletonAnimationFile->CreateNewLine();
			skeletonAnimationFile->Write("preState", BehaviourToString(channel->mPreState));
			skeletonAnimationFile->CreateNewLine();
			skeletonAnimationFile->Write("postState", BehaviourToString(channel->mPostState));

			skeletonAnimationFile->CreateNewLine();
			skeletonAnimationFile->Write("position", channel->mNumPositionKeys);
			for (uint i = 0; i < channel->mNumPositionKeys; i++)
			{
				const aiVectorKey& key = channel->mPositionKeys[i];
				skeletonAnimationFile->CreateNewLine();
				skeletonAnimationFile->Write(key.mTime / ticksPerSecond, key.mValue.x, key.mValue.y, key.mValue.z);
			}

			skeletonAnimationFile->CreateNewLine();
			skeletonAnimationFile->Write("scale", channel->mNumScalingKeys);
			for (uint i = 0; i < channel->mNumScalingKeys; i++)
			{
				const aiVectorKey& key = channel->mScalingKeys[i];
				skeletonAnimationFile->CreateNewLine();
				skeletonAnimationFile->Write(key.mTime / ticksPerSecond, key.mValue.x, key.mValue.y, key.mValue.z);
			}

			skeletonAnimationFile->CreateNewLine();
			skeletonAnimationFile->Write("rotation", channel->mNumRotationKeys);
			for (uint i = 0; i < channel->mNumRotationKeys; i++)
			{
				const aiQuatKey& key = channel->mRotationKeys[i];
				skeletonAnimationFile->CreateNewLine();
				skeletonAnimationFile->Write(key.mTime / ticksPerSecond, key.mValue.x, key.mValue.y, key.mValue.z, key.mValue.w);
			}
		}

		Core::String BehaviourToString(aiAnimBehaviour behaviour)
		{
			switch (behaviour)
			{
				case aiAnimBehaviour_CONSTANT:
				{
					return "constant";
				}
				case aiAnimBehaviour_DEFAULT:
				{
					return "default";
				}
				case aiAnimBehaviour_LINEAR:
				{
					return "linear";
				}
				case aiAnimBehaviour_REPEAT:
				{
					return "repeat";
				}
				default:
				{
					return "unknown";
				}
			}
		}
	}
}
