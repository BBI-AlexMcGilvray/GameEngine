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
				String line = modelFile.GetLine();

				IOSStreamChar lineStream(line);

				lineStream >> Material.Name.H;
				lineStream >> Mesh.Name.H;
				lineStream >> Skeleton.Name.H;
				lineStream >> Texture.Name.H;
			}
			catch (EOFException& e)
			{
				std::cout << e.GetError() << std::endl;
			}

			modelFile.Close();
		}
	}
}