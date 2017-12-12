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
			List<uint> indices;

			enum ReadState
			{
				Started,
				Positions,
				Normals,
				Indices
			};
			ReadState readState = ReadState::Started;

			String line;
			while (std::getline(meshFile, line))
			{
				IOSStreamChar lineStream(line);

				String word;
				lineStream >> word;

				String comma;
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
				else
				{
					switch (readState)
					{
						case ReadState::Positions:
						{
							Float3 newPosition;
							lineStream >> newPosition.X;
							lineStream >> comma;
							lineStream >> newPosition.Y;
							lineStream >> comma;
							lineStream >> newPosition.Z;

							Push(positions, newPosition);

							break;
						}
						case ReadState::Normals:
						{
							Float3 newNormal;
							lineStream >> newNormal.X;
							lineStream >> comma;
							lineStream >> newNormal.Y;
							lineStream >> comma;
							lineStream >> newNormal.Z;

							Push(normals, newNormal);

							break;
						}
						case ReadState::Indices:
						{
							uint newIndex;
							lineStream >> newIndex;

							Push(indices, newIndex);

							break;
						}
						case ReadState::Started:
						{
							cout << "Unsuppoerted specifier read in mesh file <<" + fileName + ">>" << endl;
							break;
						}
					}
				}

				for (auto& index : indices)
				{
					VertexCount++;

					Push(Vertices, VertexDataBase(positions[index], normals[index]));
				}
			}
		}
	}
}