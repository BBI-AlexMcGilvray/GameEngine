#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/ListDefs.h"
#include "Core/IO/Headers/File.h"

using namespace std;

struct aiScene;
struct aiMesh;
struct aiMaterial;

namespace Data
{
	namespace DataExport
	{
		enum class ModelType
		{
			Simple,
			Static,
			Animated,
			Unknown
		};

		void ConvertModelsInFolder(Core::Ptr<Core::IO::File> directAssets, Core::String folder);

		void ConvertFilesForScene(Core::Ptr<Core::IO::File> directAssets, Core::Ptr<Core::IO::File> sceneFile, Core::String sceneName, Core::List<Core::Pair<ModelType, Core::String>>& models, Core::List<Core::Pair<ModelType, Core::String>>& meshes, Core::List<Core::String>& materials, Core::List<Core::String>& skeletons, Core::List<Core::String>& skeletonAnimations);

		void DirectModels(Core::Ptr<Core::IO::File> directAssets, Core::List<Core::Pair<ModelType, Core::String>>& models);
		void DirectMeshes(Core::Ptr<Core::IO::File> directAssets, Core::List<Core::Pair<ModelType, Core::String>>& meshes);
		void DirectMaterials(Core::Ptr<Core::IO::File> directAssets, Core::List<Core::String>& materials);
		void DirectSkeletons(Core::Ptr<Core::IO::File> directAssets, Core::List<Core::String>& skeletons);
		void DirectSkeletonAnimations(Core::Ptr<Core::IO::File> directAssets, Core::List<Core::String>& skeletonAnimations);

		Core::String FixAnimationName(Core::String name);
	}
}
