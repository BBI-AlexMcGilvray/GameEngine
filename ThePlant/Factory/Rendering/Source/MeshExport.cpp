#pragma once

#include "Factory/Rendering/Headers/MeshExport.h"

#include "Core/Headers/ListDefs.h"
#include "Core/Headers/Hash.h"

#include "Core/Debugging/Headers/Macros.h"

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
		void CreateFileForMesh(Ptr<IO::File> directAssets, const aiMesh* mesh, String name)
		{
			List<Float3> positions;
			positions.reserve(mesh->mNumVertices);

			List<Float3> normals;
			normals.reserve(mesh->mNumVertices);

			// this should be changed to handle multiple textures, and the saving of each one's data
			List<Float2> uvs;
			if (mesh->HasTextureCoords(0))
			{
				uvs.reserve(mesh->mNumVertices);
			}

			LOG("Reading positions and normals from ASSIMP mesh data...");
			Float3 currentPosition;
			Float3 currentNormal;
			Float2 currentUV;
			for (uint vertexIndex = 0u; vertexIndex < mesh->mNumVertices; vertexIndex++)
			{
				// get vertex and normal from mesh data
				aiVector3D meshVertex = mesh->mVertices[vertexIndex];
				currentPosition.X = meshVertex.x;
				currentPosition.Y = meshVertex.y;
				currentPosition.Z = meshVertex.z;
				Push(positions, currentPosition);

				aiVector3D meshNormal = mesh->mNormals[vertexIndex];
				currentNormal.X = meshNormal.x;
				currentNormal.Y = meshNormal.y;
				currentNormal.Z = meshNormal.z;
				Push(normals, currentNormal);
				
				// this should be changed to handle multiple textures, and the saving of each one's data
				if (mesh->HasTextureCoords(0))
				{
					aiVector3D meshUV = mesh->mTextureCoords[0][vertexIndex];
					currentUV.X = meshUV.x;
					currentUV.Y = meshUV.y;
					Push(uvs, currentUV);
				}
			}

			// maximum of 4 bones per vertex
			List<List<Pair<String, float>>> boneWeights = List<List<Pair<String, float>>>(mesh->mNumVertices);

			if (mesh->HasBones())
			{
				for (uint i = 0; i < mesh->mNumBones; i++)
				{
					Ptr<aiBone> bone = mesh->mBones[i];
					for (uint j = 0; j < bone->mNumWeights; j++)
					{
						aiVertexWeight& boneWeight = bone->mWeights[j];
						
						Push(boneWeights[boneWeight.mVertexId], Pair<String, float>(String(bone->mName.C_Str()), boneWeight.mWeight));
					}
				}
			}

			// get all indices out of assimp format int othe vector
			List<uint> faces;
			faces.reserve(mesh->mNumFaces * 3u); // 3 indices per triangle

			LOG("Reading [position/normal] indices used by each face...");
			for (uint32_t faceIndex = 0u; faceIndex < mesh->mNumFaces; faceIndex++)
			{
				// 3 indices for each face of the triangle
				faces.push_back(mesh->mFaces[faceIndex].mIndices[0u]);
				faces.push_back(mesh->mFaces[faceIndex].mIndices[1u]);
				faces.push_back(mesh->mFaces[faceIndex].mIndices[2u]);
			}

			FilePath meshFilePath = FilePath{ GetCWD() + "/Resources/ExportedAssets/Meshes/", ToString(HashValue(name)) + ".msh" };
			File meshFile = File(meshFilePath, ios::out);
			meshFile.Open();

			if (!meshFile.FileStream.is_open())
			{
				LOG("Could not open file <<" + meshFilePath.GetFullPath() + ">>");
				return;
			}

			LOG("Writing to <<" + meshFilePath.GetFullPath() + ">>");

			meshFile.Write("positions", mesh->mNumVertices);
			meshFile.CreateNewLine();
			for (uint32_t positionIndex = 0u; positionIndex < positions.size(); positionIndex++)
			{
				meshFile.Write((positions[positionIndex].X / 100.0f), (positions[positionIndex].Y / 100.0f), (positions[positionIndex].Z / 100.0f));
				meshFile.CreateNewLine();
			}

			meshFile.Write("normals", mesh->mNumVertices);
			meshFile.CreateNewLine();
			for (uint32_t normalIndex = 0u; normalIndex < normals.size(); normalIndex++)
			{
				meshFile.Write(normals[normalIndex].X, normals[normalIndex].Y, normals[normalIndex].Z);
				meshFile.CreateNewLine();
			}

			// this should be changed to handle multiple textures, and the saving of each one's data
			if (mesh->HasTextureCoords(0))
			{
				meshFile.Write("uvs", mesh->mNumVertices);
				meshFile.CreateNewLine();
				for (uint uvIndex = 0u; uvIndex < uvs.size(); uvIndex++)
				{
					meshFile.Write(uvs[uvIndex].X, uvs[uvIndex].Y);
					meshFile.CreateNewLine();
				}
			}

			if (mesh->HasBones())
			{
				meshFile.Write("bones", mesh->mNumVertices);
				meshFile.CreateNewLine();
				for (uint boneIndex = 0u; boneIndex < boneWeights.size(); boneIndex++)
				{
					for (uint referenceIndex = 0; referenceIndex < boneWeights[boneIndex].size(); referenceIndex++)
					{
						meshFile.Write(boneWeights[boneIndex][referenceIndex].first, boneWeights[boneIndex][referenceIndex].second);
						if (referenceIndex < boneWeights[boneIndex].size() - 1)
						{
							meshFile.Write(" ");
						}
					}
					meshFile.CreateNewLine();
				}
			}

			meshFile.Write("indices", mesh->mNumFaces * 3u);
			meshFile.CreateNewLine();
			for (uint32_t faceIndex = 0u; faceIndex < faces.size(); faceIndex += 3) // += 3 because 3 vertices to a face (triangles)
			{
				meshFile.Write(faces[faceIndex], faces[faceIndex + 1], faces[faceIndex + 2]);

				if (faceIndex < faces.size() - 1)
				{
					meshFile.CreateNewLine();
				}
			}

			meshFile.Close();
		}
	}
}
