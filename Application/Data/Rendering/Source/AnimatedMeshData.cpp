#include "Data/Rendering/Headers/AnimatedMeshData.h"

#include "Core/IO/Headers/IOUtils.h"

#include "Core/Debugging/Headers/Macros.h"

using namespace Core;
using namespace Core::IO;

namespace Data
{
	namespace Rendering
	{
		AnimatedMeshData::AnimatedMeshData(AssetName<AnimatedMeshData> asset)
		{
			File meshFile = OpenFileI(asset.GetFilePath());

			MESSAGE(meshFile.FileStream.is_open(), "FAILED TO READ FILE <<" + asset.GetFilePath().GetFullPath() + ">>");

			List<Float3> positions;
			List<Float3> normals;
			List<Float2> uvs;
			List<List<String>> boneNames;
			List<Float4> boneWeights;
			List<Uint3> indices;

			enum class ReadState
			{
				Started,
				Pending,
				Positions,
				Normals,
				UVs,
				Bones,
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
							readState = ReadState::Bones;
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
						case ReadState::Bones:
						{
							string bone1;
							string bone2;
							string bone3;
							string bone4;
							Float4 newBoneWeight;

							String comma;

							lineStream >> bone1;
							lineStream >> newBoneWeight.X;

							lineStream >> comma;

							lineStream >> bone2;
							lineStream >> newBoneWeight.Y;

							lineStream >> comma;

							lineStream >> bone3;
							lineStream >> newBoneWeight.Z;

							lineStream >> comma;

							lineStream >> bone4;
							lineStream >> newBoneWeight.W;

							List<String> newBoneString = { bone1, bone2, bone3, bone4 };
							if (bone1 == "")
							{
								newBoneWeight.X = 0;
							}
							if (bone2 == "")
							{
								newBoneWeight.Y = 0;
							}
							if (bone3 == "")
							{
								newBoneWeight.Z = 0;
							}
							if (bone4 == "")
							{
								newBoneWeight.W = 0;
							}

							Push(boneNames, newBoneString);
							Push(boneWeights, newBoneWeight);

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
							cout << "Unsupported specifier read in mesh file <<" + asset.GetFilePath().GetFullPath() + ">>" << endl;
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

					LOG("Position values should be modified on the data side!");
					Push(Vertices, AnimatedVertexDataBase(positions[v]*500.0f, normals[v], uvs[v], boneNames[v], boneWeights[v]));
				}
			}
		}
	}
}