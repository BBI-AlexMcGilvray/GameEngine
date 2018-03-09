#include "Data/Rendering/Headers/MeshData.h"

#include "Data/IO/Headers/IOUtils.h"

#include "Core/Debugging/Headers/Macros.h"

using namespace Data::IO;
using namespace Core;

namespace Data
{
	namespace Rendering
	{
		MeshData::MeshData(String fileName)
		{
			IFStreamChar meshFile = OpenFileI(fileName);

			MESSAGE(meshFile.is_open(), "FAILED TO READ FILE <<" + fileName + ">>");

			List<Float3> positions;
			List<Float3> normals;
			List<Uint3> indices;

			enum class ReadState
			{
				Started,
				Pending,
				Positions,
				Normals,
				Indices
			};
			ReadState readState = ReadState::Started;
			int stateCount = 0;

			String line;
			while (std::getline(meshFile, line))
			{
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
							cout << "Unsuppoerted specifier read in mesh file <<" + fileName + ">>" << endl;
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

			for (auto& index : indices)
			{
				Float3 faceNormal = { 0.0f };

				for (auto& v : index.Axes)
				{
					faceNormal += normals[v];
				}
				faceNormal /= 3.0f; // each face should average out each vertex normal to be more accurate for the face

				for (auto& v : index.Axes)
				{
					VertexCount++;

					Push(Vertices, VertexDataBase(positions[v], faceNormal));
				}
			}
		}
	}
}