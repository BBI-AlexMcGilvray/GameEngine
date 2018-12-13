#include "Data/Rendering/Headers/AnimatedModelData.h"

#include "Core/IO/Headers/IOUtils.h"

#include "Core/Debugging/Headers/Macros.h"

using namespace Core;
using namespace Core::IO;
using namespace Core::Math;

namespace Data
{
	namespace Rendering
	{
		AnimatedModelData::AnimatedModelData(AssetName<AnimatedModelData> asset)
		{
			File modelFile = OpenFileI(asset.GetFilePath());

			MESSAGE(modelFile.FileStream.is_open(), "FAILED TO READ FILE <<" + asset.GetFilePath().GetFullPath() + ">>");

			try
			{
				while (true)
				{
					String line = modelFile.GetLine();

					IOSStreamChar lineStream(line);

					String word;
					lineStream >> word;

					if (word == "mesh")
					{
						lineStream >> Mesh.Name.H;
					}
					else if (word == "material")
					{
						lineStream >> Material.Name.H;
					}
					else if (word == "skeleton")
					{
						lineStream >> Skeleton.Name.H;
					}
					else if (word == "texture")
					{
						lineStream >> Texture.Name.H;
					}
				}
			}
			catch (EOFException& e)
			{
				std::cout << e.GetError() << std::endl;
			}

			modelFile.Close();
		}
	}
}