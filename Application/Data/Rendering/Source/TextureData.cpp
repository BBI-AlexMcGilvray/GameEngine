#include "Data/Rendering/Headers/TextureData.h"

#include "Core/IO/Headers/IOUtils.h"

#include "Core/Debugging/Headers/Macros.h"

using namespace Core;
using namespace Core::IO;

namespace Data
{
	namespace Rendering
	{
		TextureData::TextureData(AssetName<TextureData> asset)
		{
			File textureFile = OpenFileI(asset.GetFilePath());

			MESSAGE(textureFile.FileStream.is_open(), "FAILED TO READ FILE <<" + asset.GetFilePath().GetFullPath() + ">>");

			try
			{
				String line = textureFile.GetLine();

				IOSStreamChar lineStream(line);

				lineStream >> Size.X;
				lineStream >> Size.Y;

				lineStream >> ImageFile;
			}
			catch (EOFException& e)
			{
				// this is how this should end (for now at least)
				std::cout << e.GetError() << std::endl;
			}

			textureFile.Close();
		}
	}
}