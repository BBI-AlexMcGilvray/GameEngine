#include "Factory/Headers/ExportData.h"

#include "Core/Logging/Logger.h"

#include "Core/Headers/Hash.h"

#include "Core/IO/Headers/IOUtils.h"
#include "Core/IO/Headers/Folder.h"

#include "Factory/CustomData/Headers/DataCreation.h"

#include "Factory/Rendering/Headers/SceneConversion.h"
#include "Factory/Rendering/Headers/ShaderExport.h"

namespace Data
{
	namespace DataExport
	{
		namespace 
		{
			const std::string EXPORTING = "Exporting";
		}

		void ExportData()
		{
			// this CWD is wrong outside of debugging - need to update launch.json to match the 'real' CWD
			FilePath configPath = FilePath{ GetCWD() + "Factory/Configs/", "FactoryConfig.txt" };
			File configFile = File(configPath, std::ios::in | std::ios::out);
			configFile.Open();
			Config factoryConfig = Config(configFile);

			CORE_LOG(EXPORTING, "Starting to export data");
			auto directPath = FilePath{ GetCWD() + factoryConfig.getValue("exportPath"), factoryConfig.getValue("directAssetsFile") };
			auto directAssets = File(directPath, ios::out);
			directAssets.Open();
			directAssets.Clear();

			InitializeAssetsFile(&directAssets);

			// Not exporting custom data since it is not needed atm
			//ExportCustomData(&directAssets);
			ExportRenderingData(&directAssets, factoryConfig);

			FinalizeAssetsFile(&directAssets);

			directAssets.Close();
			CORE_LOG(EXPORTING, "Finished exporting data");
		}

		void ExportCustomData(Ptr<File> directAssets, Config& config)
		{
			CreateFolder(GetCWD() + config.getValue("exportPath") + config.getValue("customDataExportPath"));

			CORE_LOG(EXPORTING, "Starting to export custom data");
			auto dbPath = FilePath{ GetCWD() + config.getValue("importPath") + config.getValue("customDataImportPath"), config.getValue("dataDBImport") };
			SQLInstance db = SQLInstance(dbPath);
			db.Open();

			ExportCustomData(&db, directAssets);

			db.Close();
			CORE_LOG(EXPORTING, "Finished exporting custom data");
		}

		void ExportRenderingData(Ptr<File> directAssets, Config& config)
		{
			CORE_LOG(EXPORTING, "Starting to export rendering data");

			// maybe this should be it's own function?
			CreateFolder(GetCWD() + config.getValue("exportPath") + config.getValue("modelsExportPath"));
			CreateFolder(GetCWD() + config.getValue("exportPath") + config.getValue("materialsExportPath"));
			CreateFolder(GetCWD() + config.getValue("exportPath") + config.getValue("meshesExportPath"));
			CreateFolder(GetCWD() + config.getValue("exportPath") + config.getValue("skeletonsExportPath"));
			CreateFolder(GetCWD() + config.getValue("exportPath") + config.getValue("skeletonAnimationsExportPath"));
			CreateFolder(GetCWD() + config.getValue("exportPath") + config.getValue("texturesExportPath"));
			CreateFolder(GetCWD() + config.getValue("exportPath") + config.getValue("shadersExportPath"));
			CreateFolder(GetCWD() + config.getValue("exportPath") + config.getValue("shadersExportPath") + config.getValue("fragmentShadersExportPath"));
			CreateFolder(GetCWD() + config.getValue("exportPath") + config.getValue("shadersExportPath") + config.getValue("vertexShadersExportPath"));

			// in the future, this should likely also reference a database that is used to get specific file locations
			ConvertModelsInFolder(config, directAssets, GetCWD() + config.getValue("importPath") + config.getValue("modelsImportPath"));
			ExportShadersInFolder(config, directAssets, GetCWD() + config.getValue("importPath") + config.getValue("shadersImportPath"));

			CORE_LOG(EXPORTING, "Finished exporting rendering data");
		}

		void InitializeAssetsFile(Ptr<File> directAssets)
		{
			auto header = R"(
#pragma once

#include "Data/Headers/AssetType.h"
#include "Data/Headers/AssetName.h"

#include "CustomAssets.h"

#include "Data/Rendering/Headers/AnimatedMeshData.h"
#include "Data/Rendering/Headers/AnimatedModelData.h"
#include "Data/Rendering/Headers/MaterialData.h"
#include "Data/Rendering/Headers/ShaderData.h"
#include "Data/Rendering/Headers/SkeletonAnimationData.h"
#include "Data/Rendering/Headers/SkeletonData.h"
#include "Data/Rendering/Headers/SimpleMeshData.h"
#include "Data/Rendering/Headers/SimpleModelData.h"
#include "Data/Rendering/Headers/StaticMeshData.h"
#include "Data/Rendering/Headers/StaticModelData.h"
#include "Data/Rendering/Headers/TextureData.h"

namespace Data
{
	/*
		This file has been auto-generated

		DO NOT CHANGE
	*/
	struct Assets
	{
)";
			directAssets->Write(header);
		}

		void FinalizeAssetsFile(Ptr<File> directAssets)
		{
			auto footer = R"(
	};
	const Assets Ast;
	}
)";
			directAssets->Write(footer);
		}

		// none of the below should be here, but for the sake of getting this running without re-configuring
		// the whole mesh/mat export data sequence		
		void ExportDirectReference_Open(std::string name, std::string acronym, Ptr<File> directAssets)
		{
			directAssets->Write("\t\tstruct " + name);
			directAssets->CreateNewLine();
			directAssets->Write("\t\t{");
			directAssets->CreateNewLine();
		}

		void ExportDirectReference_Close(std::string name, std::string acronym, Ptr<File> directAssets)
		{
			directAssets->Write("\t\t};");
			directAssets->CreateNewLine();
			directAssets->Write("\t\tconst " + name + " " + acronym + ";");
			directAssets->CreateNewLine();
		}
	}
}