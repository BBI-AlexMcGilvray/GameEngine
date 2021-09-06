#pragma once

#include <array>

#include "Factory/Rendering/Headers/MeshExport.h"

#include "Core/Headers/ListDefs.h"
#include "Core/Headers/Hash.h"

#include "Core/Logging/Logger.h"

#include "Core/IO/Headers/File.h"
#include "Core/IO/Headers/Folder.h"
#include "Core/IO/Headers/IOUtils.h"

#include "Core/Math/Headers/Vector2.h"
#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/Vector4.h"

#include "Core/Serialization/Formats/JSON/JSON.h"
#include "Core/Serialization/Serialization.h"

#include "Data/Headers/SerializationUtils.h"
#include "Data/Rendering/Headers/AnimatedMeshData.h"
#include "Data/Rendering/Headers/SimpleMeshData.h"
#include "Data/Rendering/Headers/StaticMeshData.h"

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
		namespace
		{
			const std::string MESH_EXPORT = "Material Export";
		}
		
		void FillPositionData(std::vector<Core::Math::Float3>& positions, const aiMesh* mesh)
		{
			positions.reserve(mesh->mNumVertices);
			
			Core::Math::Float3 currentPosition;
			for (uint vertexIndex = 0u; vertexIndex < mesh->mNumVertices; vertexIndex++)
			{
				// get vertex and normal from mesh data
				aiVector3D meshVertex = mesh->mVertices[vertexIndex];

				currentPosition.X = meshVertex.x;
				currentPosition.Y = meshVertex.y;
				currentPosition.Z = meshVertex.z;

				positions.push_back(currentPosition);
			}
		}
		
		void FillNormalData(std::vector<Core::Math::Float3>& normals, const aiMesh* mesh)
		{
			normals.reserve(mesh->mNumVertices);
			
			Core::Math::Float3 currentNormal;
			for (uint vertexIndex = 0u; vertexIndex < mesh->mNumVertices; vertexIndex++)
			{
				// get vertex and normal from mesh data
				aiVector3D meshNormal = mesh->mNormals[vertexIndex];

				currentNormal.X = meshNormal.x;
				currentNormal.Y = meshNormal.y;
				currentNormal.Z = meshNormal.z;

				normals.push_back(currentNormal);
			}
		}
		
		void FillUVData(std::vector<Core::Math::Float2>& uvs, const aiMesh* mesh)
		{
			uvs.reserve(mesh->mNumVertices);
			
			Core::Math::Float2 currentUV;
			for (uint vertexIndex = 0u; vertexIndex < mesh->mNumVertices; vertexIndex++)
			{
				// this should be changed to handle multiple textures, and the saving of each one's data
				if (mesh->HasTextureCoords(0))
				{
					aiVector3D meshUV = mesh->mTextureCoords[0][vertexIndex];

					currentUV.X = meshUV.x;
					currentUV.Y = meshUV.y;

					uvs.push_back(currentUV);
				}
				else
				{
					throw; // why fill in UV data if there is none?
				}
			}
		}
		
		void FillBoneData(std::vector<std::array<std::string, 4>>& boneNames, std::vector<Core::Math::Float4>& boneWeights, const aiMesh* mesh)
		{
			boneNames.resize(mesh->mNumVertices);
			boneWeights.resize(mesh->mNumVertices);

			// since our vertices only have 4 bones that they can relate to, this is how we keep track which of the 4 bones is being references
			std::vector<uint> vertexIndex(mesh->mNumVertices);

			if (mesh->HasBones())
			{
				for (uint i = 0; i < mesh->mNumBones; i++)
				{
					Ptr<aiBone> bone = mesh->mBones[i];
					for (uint j = 0; j < bone->mNumWeights; j++)
					{
						aiVertexWeight& boneWeight = bone->mWeights[j];
						
						uint vertex = boneWeight.mVertexId;

						if (vertex > 4)
						{
							throw; // we only allow for 4 bones per vertex
						}

						boneNames[vertex][vertexIndex[vertex]] = bone->mName.C_Str();
						boneWeights[vertex][vertexIndex[vertex]] = boneWeight.mWeight;
						vertexIndex[vertex] += 1;
					}
				}
			}
			else
			{
				throw; // why get to here if there are no bones?
			}
		}

		void FillIndicesData(std::vector<Core::Math::Uint3>& indices, uint& numVertices, const aiMesh* mesh)
		{
			indices.reserve(mesh->mNumFaces);
			
			uint vertexCount = 0;
			Core::Math::Uint3 currentIndices;
			for (uint32_t faceIndex = 0u; faceIndex < mesh->mNumFaces; faceIndex++)
			{
				currentIndices.X = mesh->mFaces[faceIndex].mIndices[0u];
				currentIndices.Y = mesh->mFaces[faceIndex].mIndices[1u];
				currentIndices.Z = mesh->mFaces[faceIndex].mIndices[2u];

				indices.push_back(currentIndices);

				vertexCount += 3;
			}
			
			numVertices = vertexCount;
		}

		Core::Serialization::Format::JSON SerializeAnimatedMesh(const std::string& name, const aiMesh* mesh)
		{
			Data::Rendering::AnimatedMeshData meshData;

			FillPositionData(meshData.positions, mesh);
			FillNormalData(meshData.normals, mesh);
			FillUVData(meshData.uvs, mesh);
			FillBoneData(meshData.boneNames, meshData.boneWeights, mesh);
			FillIndicesData(meshData.indices, meshData.vertexCount, mesh);

			return Core::Serialize<Core::Serialization::Format::JSON>(meshData);
		}
		
		Core::Serialization::Format::JSON SerializeSimpleMesh(const std::string& name, const aiMesh* mesh)
		{
			Data::Rendering::SimpleMeshData meshData;

			FillPositionData(meshData.positions, mesh);
			FillNormalData(meshData.normals, mesh);
			FillIndicesData(meshData.indices, meshData.vertexCount, mesh);

			return Core::Serialize<Core::Serialization::Format::JSON>(meshData);
		}
		
		Core::Serialization::Format::JSON SerializeStaticMesh(const std::string& name, const aiMesh* mesh)
		{
			Data::Rendering::StaticMeshData meshData;

			FillPositionData(meshData.positions, mesh);
			FillNormalData(meshData.normals, mesh);
			FillUVData(meshData.uvs, mesh);
			FillIndicesData(meshData.indices, meshData.vertexCount, mesh);

			return Core::Serialize<Core::Serialization::Format::JSON>(meshData);
		}

		void CreateFileForMesh(Config& config, Ptr<IO::File> directAssets, const aiMesh* mesh, String name)
		{
			Core::Serialization::Format::JSON meshAsJSON;
			bool hasUVs = mesh->HasTextureCoords(0);
			bool hasBones = mesh->HasBones();
			if (hasBones)
			{
				if (!hasUVs)
				{
					throw; // only support animated models with uvs
				}

				meshAsJSON = SerializeAnimatedMesh(name, mesh);
			}
			else if (hasUVs)
			{
				meshAsJSON = SerializeStaticMesh(name, mesh);
			}
			else
			{
				meshAsJSON = SerializeSimpleMesh(name, mesh);
			}

			FilePath meshFilePath = FilePath{ GetCWD() + "/Resources/ExportedAssets/Meshes/", to_string(HashValue(name)) + ".msh" };
			File meshFile = File(meshFilePath, ios::out);
			meshFile.Open();

			if (!meshFile.FileStream.is_open())
			{
				CORE_LOG(MESH_EXPORT, "Could not open file <<" + meshFilePath.GetFullPath() + ">>");
				return;
			}

			CORE_LOG(MESH_EXPORT, "Writing to <<" + meshFilePath.GetFullPath() + ">>");

			meshFile.Write(meshAsJSON.ToString(Core::Serialization::Format::Style::Readable));

			meshFile.Close();
		}
	}
}
