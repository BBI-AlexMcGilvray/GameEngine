#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/ListDefs.h"

#include "Core/IO/Headers/File.h"

#include "ASSIMP/anim.h"

struct aiScene;
struct aiMesh;
struct aiNode;
struct aiNodeAnim;
struct aiAnimation;

namespace Data
{
	namespace DataExport
	{
		void CreateFileForSkeletonAnimation(Core::Ptr<Core::IO::File> directAssets, Core::Ptr<aiAnimation> animation, Core::Ptr<const aiNode> rootNode, Core::Ptr<const aiMesh> mesh, Core::uint meshIndex, Core::String name);

		void AddChannelToFile(Core::Ptr<Core::IO::File> skeletonAnimationFile, Core::Ptr<const aiNodeAnim> channel, double ticksPerSecond);
		Core::String BehaviourToString(aiAnimBehaviour behaviour);
	}
}
