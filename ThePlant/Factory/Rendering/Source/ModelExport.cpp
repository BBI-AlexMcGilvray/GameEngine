#pragma once

#include "Factory/Rendering/Headers/MeshExport.h"

#include "Core/Headers/ListDefs.h"
#include "Core/Headers/Hash.h"

#include "Core/IO/Headers/File.h"
#include "Core/IO/Headers/Folder.h"
#include "Core/IO/Headers/IOUtils.h"

#include "Core/Math/Headers/Vector2.h"
#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/Vector4.h"

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
		void CreateFileForModel(Ptr<File> directAssets, Ptr<const aiScene> scene, uint meshIndex, String name)
		{
			FilePath meshFilePath = FilePath{ GetCWD() + "/Resources/ExportedAssets/Models/", ToString(HashValue(name)) + ".mdl" };
			File meshFile = File(meshFilePath, std::ios::out);
			meshFile.Open();

			meshFile.Write("mesh", ToString(HashValue(name)));
			meshFile.CreateNewLine();

			meshFile.Write("material", ToString(HashValue(name)));

			if (scene->mMeshes[meshIndex]->HasBones())
			{
				meshFile.CreateNewLine();
				meshFile.Write("skeleton", ToString(HashValue(name)));
			}

			meshFile.Close();
		}
	}
}
