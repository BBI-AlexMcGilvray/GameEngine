#include "Data/Rendering/Headers/SimpleModelData.h"

#include "Core/IO/Headers/IOUtils.h"

#include "Core/Debugging/Headers/Macros.h"

using namespace Core;
using namespace Core::IO;
using namespace Core::Math;

namespace Data
{
	namespace Rendering
	{
		SimpleModelData::SimpleModelData(AssetName<SimpleModelData> asset)
		{
			File modelFile = OpenFileI(asset.GetFilePath());

			MESSAGE(modelFile.FileStream.is_open(), "FAILED TO READ FILE <<" + asset.GetFilePath().GetFullPath() + ">>");

			try
			{
				String line = modelFile.GetLine();

				IOSStreamChar lineStream(line);

				lineStream >> Mesh.Name.H;
				lineStream >> Material.Name.H;
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