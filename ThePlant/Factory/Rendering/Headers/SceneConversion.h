#pragma once

#include <string>
#include <utility>
#include <vector>

#include "Core/Headers/PtrDefs.h"
#include "Core/IO/Headers/File.h"

#include "Factory/Headers/Config.h"

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

		void ConvertModelsInFolder(Config& config, Core::Ptr<Core::IO::File> directAssets, std::string folder);

		void ConvertFilesForScene(Config& config, Core::Ptr<Core::IO::File> directAssets, Core::Ptr<Core::IO::File> sceneFile, std::string sceneName, std::vector<std::pair<ModelType, std::string>>& models, std::vector<std::pair<ModelType, std::string>>& meshes, std::vector<std::string>& materials, std::vector<std::string>& skeletons, std::vector<std::string>& skeletonAnimations);

		void DirectModels(Core::Ptr<Core::IO::File> directAssets, std::vector<std::pair<ModelType, std::string>>& models);
		void DirectMeshes(Core::Ptr<Core::IO::File> directAssets, std::vector<std::pair<ModelType, std::string>>& meshes);
		void DirectMaterials(Core::Ptr<Core::IO::File> directAssets, std::vector<std::string>& materials);
		void DirectSkeletons(Core::Ptr<Core::IO::File> directAssets, std::vector<std::string>& skeletons);
		void DirectSkeletonAnimations(Core::Ptr<Core::IO::File> directAssets, std::vector<std::string>& skeletonAnimations);

		std::string FixAnimationName(std::string name);
	}
}
