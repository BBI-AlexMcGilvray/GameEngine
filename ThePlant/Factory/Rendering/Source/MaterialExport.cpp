#pragma once

#include "Factory/Rendering/Headers/MaterialExport.h"

#include "Core/Headers/ListDefs.h"
#include "Core/Headers/Hash.h"

#include "Core/Logging/Logger.h"

#include "Core/IO/Headers/File.h"
#include "Core/IO/Headers/Folder.h"
#include "Core/IO/Headers/IOUtils.h"

#include "Core/Serialization/Formats/JSON/JSON.h"
#include "Core/Serialization/Serialization.h"

#include "Data/Headers/SerializationUtils.h"
#include "Data/Rendering/Headers/MaterialData.h"

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
			const std::string MATERIAL_EXPORT = "Material Export";
		}

		Core::Serialization::Format::JSON SerializeMaterial(const aiMaterial* material)
		{
			// material values
			aiColor4D specularColor;
			aiColor4D diffuseColor;
			aiColor4D ambientColor;
			float shininess;

			// get values from assimp material
			aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &specularColor);
			aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuseColor);
			aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &ambientColor);
			aiGetMaterialFloat(material, AI_MATKEY_SHININESS, &shininess);

			Data::Rendering::MaterialData materialData;

			materialData.specular = Core::Math::Color(specularColor.r, specularColor.g, specularColor.b, specularColor.a);
			materialData.diffuse = Core::Math::Color(diffuseColor.r, diffuseColor.g, diffuseColor.b, diffuseColor.a);
			materialData.ambient = Core::Math::Color(ambientColor.r, ambientColor.g, ambientColor.b, ambientColor.a);
			materialData.shininess = shininess;

			return Core::Serialize<Core::Serialization::Format::JSON>(materialData);
		}

		void CreateFileForMaterial(Config& config, Core::Ptr<Core::IO::File> directAssets, const aiMaterial* material, String name)
		{
			CORE_LOG(MATERIAL_EXPORT, "Getting material information from assimp...");
			Core::Serialization::Format::JSON materialAsJSON = SerializeMaterial(material);

			// store values in file
			FilePath materialFilePath = FilePath{ GetCWD() + config.getValue("exportPath") + config.getValue("materialsPath"), to_string(HashValue(name)) + ".mat" };
			File materialFile = File(materialFilePath, std::ios::out);
			materialFile.Open();

			if (!materialFile.FileStream.is_open())
			{
				CORE_LOG(MATERIAL_EXPORT, "Could not open file <<" + materialFilePath.GetFullPath() + ">>");
				return;
			}

			materialFile.Write(materialAsJSON.ToString(Core::Serialization::Format::Style::Readable));

			materialFile.Close();
		}
	}
}
