#include "Data/Rendering/Headers/AnimatedMeshData.h"

#include "Core/IO/Headers/IOUtils.h"

#include "Core/Debugging/Headers/Macros.h"

using namespace Core;
using namespace Core::IO;

namespace Data
{
	namespace Rendering
	{
		AnimatedMeshData::AnimatedMeshData(String fileName)
		{
			File meshFile = OpenFileI(FilePath{ String("Resources/ExportedAssets/Meshes/"), fileName });

			MESSAGE(meshFile.FileStream.is_open(), "FAILED TO READ FILE <<" + fileName + ">>");

			List<Float3> positions;
			List<Float3> normals;
			List<Float2> uvs;
			List<Uint4> boneIndices;
			List<Uint3> indices;

			enum class ReadState
			{
				Started,
				Pending,
				Positions,
				Normals,
				UVs,
				BoneIndices,
				Indices
			};
			ReadState readState = ReadState::Started;
			int stateCount = 0;

			try
			{
				while (true)
				{
					String line = meshFile.GetLine();

					IOSStreamChar lineStream(line);

					if (readState == ReadState::Started || readState == ReadState::Pending)
					{
						String word;
						lineStream >> word;

						if (word == "positions")
						{
							readState = ReadState::Positions;
						}
						else if (word == "normals")
						{
							readState = ReadState::Normals;
						}
						else if (word == "uvs")
						{
							readState = ReadState::UVs;
						}
						else if (word == "bones")
						{
							readState == ReadState::BoneIndices;
						}
						else if (word == "indices")
						{
							readState = ReadState::Indices;
						}
						lineStream >> stateCount;
					}
					else
					{
						switch (readState)
						{
						case ReadState::Positions:
						{
							Float3 newPosition;
							lineStream >> newPosition.X;
							lineStream >> newPosition.Y;
							lineStream >> newPosition.Z;

							Push(positions, newPosition);

							break;
						}
						case ReadState::Normals:
						{
							Float3 newNormal;
							lineStream >> newNormal.X;
							lineStream >> newNormal.Y;
							lineStream >> newNormal.Z;

							Push(normals, newNormal);

							break;
						}
						case ReadState::UVs:
						{
							Float2 newUVs;
							lineStream >> newUVs.X;
							lineStream >> newUVs.Y;

							Push(uvs, newUVs);

							break;
						}
						case ReadState::BoneIndices:
						{
							Uint4 newBoneIndex;
							lineStream >> newBoneIndex.X;
							lineStream >> newBoneIndex.Y;
							lineStream >> newBoneIndex.Z;
							lineStream >> newBoneIndex.W;

							Push(boneIndices, newBoneIndex);

							break;
						}
						case ReadState::Indices:
						{
							Uint3 newIndex;
							lineStream >> newIndex.X;
							lineStream >> newIndex.Y;
							lineStream >> newIndex.Z;

							Push(indices, newIndex);

							break;
						}
						case ReadState::Started:
						case ReadState::Pending:
						{
							cout << "Unsupported specifier read in mesh file <<" + fileName + ">>" << endl;
							break;
						}
						}

						stateCount--;

						if (stateCount <= 0)
						{
							readState = ReadState::Pending;
						}
					}
				}
			}
			catch (EOFException& e)
			{
				// this is how this should end (for now at least)
				std::cout << e.GetError() << std::endl;
			}

			meshFile.Close();

			for (auto& index : indices)
			{
				for (auto& v : index.Axes)
				{
					VertexCount++;

					Push(Vertices, AnimatedVertexDataBase(positions[v], normals[v], uvs[v], boneIndices[v]));
				}
			}
		}
	}
}