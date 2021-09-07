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

#include "Core/Serialization/Formats/JSON/JSON.h"
#include "Core/Serialization/Serialization.h"

#include "Data/Headers/SerializationUtils.h"
#include "Data/Rendering/Headers/SkeletonAnimationData.h"

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

		Data::Rendering::AnimationBehaviour aiToCustomAnimationBehaviour(aiAnimBehaviour aiBehaviour)
		{
			switch (behaviour)
			{
				case aiAnimBehaviour_CONSTANT:
				{
					return Data::Rendering::AnimationBehaviour::Constant;
				}
				case aiAnimBehaviour_DEFAULT:
				{
					return Data::Rendering::AnimationBehaviour::Default;
				}
				case aiAnimBehaviour_LINEAR:
				{
					return Data::Rendering::AnimationBehaviour::Linear;
				}
				case aiAnimBehaviour_REPEAT:
				{
					return Data::Rendering::AnimationBehaviour::Repeat;
				}
				default:
				{
					return Data::Rendering::AnimationBehaviour::Unknown;
				}
			}
		}

		void FillInScaleFrameData(std::vector<Data::Rendering::ScaleFrameData>& scaleFrameData, const aiVectorKey& scaleKey)
		{
			Data::Rendering::ScaleFrameData scaleFrameData;

			scaleFrameData.tick = scaleKey.mTime;
			scaleFrameData.scale = Core::Math::Float3(key.mValue.x, key.mValue.y, key.mValue.z);

			scaleFrameData.push_back(scaleFrameData);
		}

		void FillInRotationFrameData(std::vector<Data::Rendering::RotationFrameData>& rotationFrameData, const aiQuatKey& rotationKey)
		{
			Data::Rendering::RotationFrameData rotationFrameData;

			rotationFrameData.tick = scaleKey.mTime;
			rotationFrameData.rotation = Core::Math::FQuaternion(key.mValue.x, key.mValue.y, key.mValue.z, key.mValue.w);

			rotationFrameData.push_back(rotationFrameData);
		}

		void FillInPositionFrameData(std::vector<Data::Rendering::PositionFrameData>& positionFrameData, const aiVectorKey& positionKey)
		{
			Data::Rendering::PositionFrameData positionFrameData;

			positionFrameData.tick = scaleKey.mTime;
			positionFrameData.scale = Core::Math::Float3(key.mValue.x, key.mValue.y, key.mValue.z);

			positionFrameData.push_back(positionFrameData);
		}

		void FillInBoneAnimationData(std::vector<Data::Rendering::BoneAnimationData>& boneAnimations, Core::Ptr<const aiNodeAnim> channel)
		{
			Data::Rendering::BoneAnimationData boneAnimationData;

			boneAnimationData.name = std::string(channel->mNodeName.C_Str());
			boneAnimationData.preBehaviour = aiToCustomAnimationBehaviour(channel->mPostState);
			boneAnimationData.postBehaviour = aiToCustomAnimationBehaviour(channel->mPreState);

			for (uint i = 0; i < channel->mNumPositionKeys; i++)
			{
				const aiVectorKey& key = channel->mPositionKeys[i];
				FillInPositionFrameData(boneAnimationData.positionChannel, key);
			}
			
			for (uint i = 0; i < channel->mNumScalingKeys; i++)
			{
				const aiVectorKey& key = channel->mScalingKeys[i];
				FillInScaleFrameData(boneAnimationData.scaleChannel, key);
			}
			
			for (uint i = 0; i < channel->mNumRotationKeys; i++)
			{
				const aiQuatKey& key = channel->mRotationKeys[i];
				FillInRotationFrameData(boneAnimationData.rotationChannel, key);
			}
		}

		Core::Serialization::Format::JSON SerializeSkeletonAnimation(Core::Ptr<const aiAnimation> animation, std::unique_ptr<ExportNode> exportSkeleton)
		{
			Data::Rendering::SkeletonAnimationData skeletonAnimationData;

			skeletonAnimationData.name = std::string(animation->mName.C_Str());
			skeletonAnimationData.ticks = animation->mDuration;
			skeletonAnimationData.ticksPerSecond = animation->mTicksPerSecond;

			for (uint i = 0; i < animation->mNumChannels; i++)
			{
				if (exportSkeleton->FindNode(animation->mChannels[i]->mNodeName.C_Str()) != nullptr)
				{
					FillInBoneAnimationData(skeletonAnimationData.boneAnimations, animation->mChannels[i]);
				}
			}

			return Core::Serialize<Core::Serialization::Format::JSON>(skeletonAnimationData);
		}

		void CreateFileForSkeletonAnimation(Config& config, Core::Ptr<Core::IO::File> directAssets, Core::Ptr<aiAnimation> animation, Ptr<const aiNode> rootNode, Ptr<const aiMesh> mesh, uint meshIndex, String name)
		{
			if (animation == nullptr)
			{
				CORE_LOG(SKELETON_ANIMATION_EXPORT, "Given skeleton <<" + name + ">> does not exist");
				return;
			}

			Ptr<const aiNode> rootNodeForMesh = FindRootNodeForMesh(rootNode, meshIndex);
			Core::UniquePtr<ExportNode> exportSkeleton = AllNodesForMesh(rootNode, mesh, meshIndex);

			// store values in file
			FilePath skeletonAnimationFilePath = FilePath{ GetCWD() + config.getValue("exportPath") + config.getValue("skeletonAnimationsPath"), to_string(HashValue(name + String(animation->mName.C_Str()))) + ".sanim" };
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
