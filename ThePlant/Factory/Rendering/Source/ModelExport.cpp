#pragma once

#include "Factory/Rendering/Headers/ModelExport.h"

#include <vector>

#include "Core/Headers/Hash.h"

#include "Core/IO/Headers/File.h"
#include "Core/IO/Headers/Folder.h"
#include "Core/IO/Headers/IOUtils.h"

#include "Core/Math/Headers/Vector2.h"
#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/Vector4.h"

#include "Core/Serialization/Formats/JSON/JSON.h"
#include "Core/Serialization/Serialization.h"

#include "Data/Headers/SerializationUtils.h"
#include "Data/Rendering/Headers/SimpleModelData.h"
#include "Data/Rendering/Headers/AnimatedModelData.h"

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
		Core::Serialization::Format::JSON SerializeSimpleModel(const std::string& name)
		{
			Data::Rendering::SimpleModelData modelData;

			modelData.material = HashValue(name);
			modelData.mesh = HashValue(name);
			// textures do not get used yet
			modelData.texture = Core::Hash::VOID;

			return Core::Serialize<Core::Serialization::Format::JSON>(modelData);
		}

		Core::Serialization::Format::JSON SerializeAnimatedModel(const std::string& name)
		{
			Data::Rendering::AnimatedModelData modelData;

			modelData.material = HashValue(name);
			modelData.mesh = HashValue(name);
			modelData.skeleton = HashValue(name);
			// textures do not get used yet
			modelData.texture = Core::Hash::VOID;
			
			return Core::Serialize<Core::Serialization::Format::JSON>(modelData);
		}

		void CreateFileForModel(Data::Config& config, Ptr<File> directAssets, Ptr<const aiScene> scene, uint meshIndex, std::string name)
		{
			Core::Serialization::Format::JSON modelAsJSON = scene->mMeshes[meshIndex]->HasBones() ? SerializeAnimatedModel(name) : SerializeSimpleModel(name);

			FilePath meshFilePath = FilePath{ GetCWD() + config.getValue("exportPath") + config.getValue("modelsPath"), to_string(HashValue(name)) + ".mdl" };
			File meshFile = File(meshFilePath, std::ios::out);
			meshFile.Open();

			// meshFile.Write("mesh", to_string(HashValue(name)));
			// meshFile.CreateNewLine();

			// meshFile.Write("material", to_string(HashValue(name)));

			// if (scene->mMeshes[meshIndex]->HasBones())
			// {
			// 	meshFile.CreateNewLine();
			// 	meshFile.Write("skeleton", to_string(HashValue(name)));
			// }
			meshFile.Write(modelAsJSON.ToString(Core::Serialization::Format::Style::Readable));

			meshFile.Close();
		}
	}
}
