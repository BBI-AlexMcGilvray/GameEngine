#pragma once

#include "Factory/Rendering/Headers/MaterialExport.h"

#include "Core/Headers/ListDefs.h"
#include "Core/Headers/Hash.h"

#include "Core/Debugging/Headers/Macros.h"

#include "Core/IO/Headers/File.h"
#include "Core/IO/Headers/Folder.h"
#include "Core/IO/Headers/IOUtils.h"

#include "ASSIMP/cimport.h"
#include "ASSIMP/scene.h"
#include "ASSIMP/postprocess.h"
#include "ASSIMP/material.h"

using namespace std;
using namespace Core;
using namespace Core::IO;

namespace Data
{
	namespace DataExport
	{
		void CreateFileForMaterial(Core::Ptr<Core::IO::File> directAssets, const aiMaterial* material, String name)
		{
			// material values
			aiColor4D specularColor;
			aiColor4D diffuseColor;
			aiColor4D ambientColor;
			float shininess;

			LOG("Getting material information from assimp...");
			// get values from assimp material
			aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &specularColor);
			aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuseColor);
			aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &ambientColor);
			aiGetMaterialFloat(material, AI_MATKEY_SHININESS, &shininess);

			// store values in file
			FilePath materialFilePath = FilePath{ GetCWD() + "/Resources/ExportedAssets/Materials/", ToString(HashValue(name)) + ".mat" };
			File materialFile = File(materialFilePath, ios::out);
			materialFile.Open();

			if (!materialFile.FileStream.is_open())
			{
				LOG("Could not open file <<" + materialFilePath.GetFullPath() + ">>");
				return;
			}

			materialFile.Write("spec ", specularColor.r, specularColor.g, specularColor.b, specularColor.a);
			materialFile.CreateNewLine();
			materialFile.Write("diff", diffuseColor.r, diffuseColor.g, diffuseColor.b, diffuseColor.a);
			materialFile.CreateNewLine();
			materialFile.Write("amb", ambientColor.r, ambientColor.g, ambientColor.b, ambientColor.a);
			materialFile.CreateNewLine();
			materialFile.Write("shin", shininess);

			materialFile.Close();
		}
	}
}
