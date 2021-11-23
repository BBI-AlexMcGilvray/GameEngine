#include "Factory\Rendering\Headers\SceneConversion.h"

#include "Factory/Headers/ExportData.h"

#include "Factory/Rendering/Headers/ModelExport.h"
#include "Factory/Rendering/Headers/MeshExport.h"
#include "Factory/Rendering/Headers/MaterialExport.h"
#include "Factory/Rendering/Headers/SkeletonExport.h"
#include "Factory/Rendering/Headers/SkeletonAnimationExport.h"

#include "Core/Headers/Hash.h"

#include "Core/Logging/Logger.h"

#include "Core/IO/Headers/Folder.h"
#include "Core/IO/Headers/IOUtils.h"

#include "ASSIMP/cimport.h"
#include "ASSIMP/scene.h"
#include "ASSIMP/postprocess.h"
#include "ASSIMP/material.h"

using namespace Core;
using namespace Core::IO;

namespace Data
{
	namespace DataExport
	{
		namespace
		{
			const std::string SCENE_CONVERSION = "Scene Conversion";
		}

		void ConvertModelsInFolder(Config& config, Ptr<File> directAssets, std::string folder)
		{
			std::vector<std::pair<ModelType, std::string>> models;
			std::vector<std::pair<ModelType, std::string>> meshes;
			std::vector<std::string> materials;
			std::vector<std::string> skeletons;
			std::vector<std::string> skeletonAnimations;

			// in the future, this should likely also reference a database that is used to get specific file locations
			FilePath listPath = FilePath{ folder, config.getValue("modelsImportFile") };
			File listFile = File(listPath, std::ios::in);
			listFile.Open();

			try
			{
				std::string line = listFile.GetLine();

				IOSStreamChar lineStream(line);

				int numAssets;
				lineStream >> numAssets;

				int assetsExported = 0;
				while (assetsExported < numAssets)
				{
					std::string line = listFile.GetLine();

					IOSStreamChar lineStream(line);

					std::string name;
					std::string path;
					std::string file;

					lineStream >> name;
					lineStream >> path;
					lineStream >> file;

					FilePath assetPath = FilePath{ folder + path, file };
					File assetFile = File(assetPath, std::ios::in);
					ConvertFilesForScene(config, directAssets, &assetFile, name, models, meshes, materials, skeletons, skeletonAnimations);

					assetsExported++;
				}
			}
			catch (Exception& e)
			{
				std::cout << e.GetError() << std::endl;
			}

			listFile.Close();

			
		}

		void ConvertFilesForScene(Config& config, Ptr<File> directAssets, Ptr<File> sceneFile, std::string sceneName, std::vector<std::pair<ModelType, std::string>>& models, std::vector<std::pair<ModelType, std::string>>& meshes, std::vector<std::string>& materials, std::vector<std::string>& skeletons, std::vector<std::string>& skeletonAnimations)
		{
			CORE_LOG(SCENE_CONVERSION, "Converting files for <<" + sceneFile->GetFullPath() + ">>");
			// this process preset also INCLUDES the flag to make all faces based on triangles
			std::string fullPathCopy = sceneFile->GetFullPath();
			Ptr<const char> c_Path = fullPathCopy.c_str();
			Ptr<const aiScene> loadedScene = aiImportFile(c_Path, aiProcessPreset_TargetRealtime_MaxQuality);

			if (!loadedScene)
			{
				CORE_LOG(SCENE_CONVERSION, "Could not load file <<" + sceneFile->GetFullPath() + ">>");
				CORE_LOG(SCENE_CONVERSION, "ASSIMP ERROR: " + std::string(aiGetErrorString()));
				return;
			}

			uint32_t numberOfMeshes = loadedScene->mNumMeshes;

			// Create model scene that holds references to all other data types (mesh, mat, skl, sanim, texture - eventually)
			// Create a file for each mesh in the parent mesh
			for (uint32_t meshIndex = 0u; meshIndex < numberOfMeshes; meshIndex++)
			{
				std::string fileName = sceneName + "_" + std::to_string(meshIndex);

				CORE_LOG(SCENE_CONVERSION, "Creating file to hold model information for <<" + fileName + ">>");
				CreateFileForModel(config, directAssets, loadedScene, meshIndex, fileName);

				CORE_LOG(SCENE_CONVERSION, "Creating file to hold mesh information for <<" + fileName + ">>");
				CreateFileForMesh(config, directAssets, loadedScene->mMeshes[meshIndex], fileName);

				if (!loadedScene->mMeshes[meshIndex]->HasBones())
				{
					models.push_back(std::pair<ModelType, std::string>(ModelType::Simple, fileName));
					meshes.push_back(std::pair<ModelType, std::string>(ModelType::Simple, fileName));

					models.push_back(std::pair<ModelType, std::string>(ModelType::Static, fileName));
					meshes.push_back(std::pair<ModelType, std::string>(ModelType::Static, fileName));
				}
				else
				{
					models.push_back(std::pair<ModelType, std::string>(ModelType::Animated, fileName));
					meshes.push_back(std::pair<ModelType, std::string>(ModelType::Animated, fileName));
				}

				CORE_LOG(SCENE_CONVERSION, "Creating file to hold material information for <<" + fileName + ">>");
				CreateFileForMaterial(config, directAssets, loadedScene->mMaterials[loadedScene->mMeshes[meshIndex]->mMaterialIndex], fileName);
				materials.push_back(fileName);

				if (loadedScene->mMeshes[meshIndex]->HasBones())
				{
					CORE_LOG(SCENE_CONVERSION, "Creating file to hold skeleton information for <<" + fileName + ">>");
					CreateFileForSkeleton(config, directAssets, loadedScene, meshIndex, fileName);
					skeletons.push_back(fileName);

					for (uint animationIndex = 0; animationIndex < loadedScene->mNumAnimations; animationIndex++)
					{
						CORE_LOG(SCENE_CONVERSION, "Creating file to hold skeleton animation information for <<" + fileName + ">>");
						// do this before the skeleton so the skeleton knows (and saves) its animations?
						CreateFileForSkeletonAnimation(config, directAssets, loadedScene->mAnimations[animationIndex], loadedScene->mRootNode, loadedScene->mMeshes[meshIndex], meshIndex, fileName);
						skeletonAnimations.push_back(fileName + "_" + FixAnimationName(std::string(loadedScene->mAnimations[animationIndex]->mName.C_Str())));
					}
				}
				else
				{
					CORE_LOG(SCENE_CONVERSION, "<<" + sceneName + ">> does not have any skeletal information");
				}
			}

			CORE_LOG(SCENE_CONVERSION, "Releasing memory for loading scene <<" + sceneFile->GetFullPath() + ">>");
			// needs to be done since assimp holds all of the memeory management for loading
			aiReleaseImport(loadedScene);
		}

		void DirectModels(Ptr<File> directAssets, std::vector<std::pair<ModelType, std::string>>& models)
		{
			// simple
			ExportDirectReference_Open("SimpleModels", "spmdl", directAssets);

			for (auto& model : models)
			{
				if (model.first == ModelType::Simple)
				{
					directAssets->Write("\t\t\tconst AssetName<Rendering::SimpleModelData> " + model.second + " = AssetName<Rendering::SimpleModelData>(AsHash(" + to_string(HashValue(model.second)) + "));");
					directAssets->CreateNewLine();
				}
			}

			ExportDirectReference_Close("SimpleModels", "spmdl", directAssets);


			// static
			ExportDirectReference_Open("StaticModels", "smdl", directAssets);

			for (auto& model : models)
			{
				if (model.first == ModelType::Static)
				{
					directAssets->Write("\t\t\tconst AssetName<Rendering::StaticModelData> " + model.second + " = AssetName<Rendering::StaticModelData>(AsHash(" + to_string(HashValue(model.second)) + "));");
					directAssets->CreateNewLine();
				}
			}

			ExportDirectReference_Close("StaticModels", "smdl", directAssets);


			// animated
			ExportDirectReference_Open("AnimatedModels", "amdl", directAssets);

			for (auto& model : models)
			{
				if (model.first == ModelType::Animated)
				{
					directAssets->Write("\t\t\tconst AssetName<Rendering::AnimatedModelData> " + model.second + " = AssetName<Rendering::AnimatedModelData>(AsHash(" + to_string(HashValue(model.second)) + "));");
					directAssets->CreateNewLine();
				}
			}

			ExportDirectReference_Close("AnimatedModels", "amdl", directAssets);
		}

		void DirectMeshes(Ptr<File> directAssets, std::vector<std::pair<ModelType, std::string>>& meshes)
		{
			// simple
			ExportDirectReference_Open("SimpleMeshes", "spmsh", directAssets);

			for (auto& mesh : meshes)
			{
				if (mesh.first == ModelType::Simple)
				{
					directAssets->Write("\t\t\tconst AssetName<Rendering::SimpleMeshData> " + mesh.second + " = AssetName<Rendering::SimpleMeshData>(AsHash(" + to_string(HashValue(mesh.second)) + "));");
					directAssets->CreateNewLine();
				}
			}

			ExportDirectReference_Close("SimpleMeshes", "spmsh", directAssets);


			// static
			ExportDirectReference_Open("StaticMeshes", "smsh", directAssets);

			for (auto& mesh : meshes)
			{
				if (mesh.first == ModelType::Static)
				{
					directAssets->Write("\t\t\tconst AssetName<Rendering::StaticMeshData> " + mesh.second + " = AssetName<Rendering::StaticMeshData>(AsHash(" + to_string(HashValue(mesh.second)) + "));");
					directAssets->CreateNewLine();
				}
			}

			ExportDirectReference_Close("StaticMeshes", "smsh", directAssets);


			// animated
			ExportDirectReference_Open("AnimatedMeshes", "amsh", directAssets);

			for (auto& mesh : meshes)
			{
				if (mesh.first == ModelType::Animated)
				{
					directAssets->Write("\t\t\tconst AssetName<Rendering::AnimatedMeshData> " + mesh.second + " = AssetName<Rendering::AnimatedMeshData>(AsHash(" + to_string(HashValue(mesh.second)) + "));");
					directAssets->CreateNewLine();
				}
			}
			
			ExportDirectReference_Close("AnimatedMeshes", "amsh", directAssets);
		}

		void DirectMaterials(Ptr<File> directAssets, std::vector<std::string>& materials)
		{
			ExportDirectReference_Open("Materials", "mat", directAssets);

			for (auto& material : materials)
			{
				directAssets->Write("\t\t\tconst AssetName<Rendering::MaterialData> " + material + " = AssetName<Rendering::MaterialData>(AsHash(" + to_string(HashValue(material)) + "));");
				directAssets->CreateNewLine();
			}

			ExportDirectReference_Close("Materials", "mat", directAssets);
		}

		void DirectSkeletons(Ptr<File> directAssets, std::vector<std::string>& skeletons)
		{
			ExportDirectReference_Open("Skeletons", "skl", directAssets);

			for (auto& skeleton : skeletons)
			{
				directAssets->Write("\t\t\tconst AssetName<Rendering::SkeletonData> " + skeleton + " = AssetName<Rendering::SkeletonData>(AsHash(" + to_string(HashValue(skeleton)) + "));");
				directAssets->CreateNewLine();
			}

			ExportDirectReference_Close("Skeletons", "skl", directAssets);
		}

		void DirectSkeletonAnimations(Ptr<File> directAssets, std::vector<std::string>& skeletonAnimations)
		{
			ExportDirectReference_Open("SkeletonAnimations", "sanim", directAssets);

			for (auto& skeletonAnimation : skeletonAnimations)
			{
				directAssets->Write("\t\t\tconst AssetName<Rendering::SkeletonAnimationData> " + skeletonAnimation + " = AssetName<Rendering::SkeletonAnimationData>(AsHash(" + to_string(HashValue(skeletonAnimation)) + "));");
				directAssets->CreateNewLine();
			}

			ExportDirectReference_Close("SkeletonAnimations", "sanim", directAssets);
		}

		std::string FixAnimationName(std::string name)
		{
			std::string fixedStr = "";

			std::vector<char> invalidChars = { '|', '~', '`', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '{', '}', '[', ']', '-', '=', '+' };
			for (uint i = 0; i < name.length(); i++)
			{
				if (std::find(invalidChars.begin(), invalidChars.end(), name[i]) != invalidChars.end())
				{
					fixedStr += '_';
				}
				else
				{
					fixedStr += name[i];
				}
			}

			return fixedStr;
		}
	}
}
